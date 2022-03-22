#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <poll.h>
#include "Parser.h"


int* cur = new int[2]; // This is a pipe for current commamd to write to
int* prev = new int[2]; // This is a pipe for prev commamd 
int* stdfd = new int[2]; // This is a array to hold STDOUT and STDIN

void *Child(std::list<Command> *commands, int index){ // child function when pid == 0
    auto it = commands->begin(); // start iterating 
    auto cmd = std::next(it, index);  // grab the current command

    // ============ set up to run command ======== //
    std::string a = cmd->name; // get the command name
    char *C = strdup(a.c_str()); // command name converted to char*

    char *argsu[cmd->args.size() + 2]; // create the args
    argsu[0] = C;
    std::list<std::string>::iterator iter; // iterator for args
    int counter = 1;
    for (iter = cmd->args.begin(); iter != (cmd->args).end(); iter++){ // loop through args and add to arr
        // load all args into char* array
        argsu[counter] = strdup(iter->c_str());
        counter++; // counter for indexing
    }
    argsu[sizeof(argsu) / sizeof(argsu[0]) - 1] = NULL; // last index is a NULL

    // ================= Start of redirection ========
    if (!(cmd -> input_file).empty()){ // read input 
        const char *file = cmd->input_file.c_str();
        int fd_ret = open(file, O_RDONLY);

        int fd_out = dup2(fd_ret, STDIN_FILENO); // Std will come from file
        close(fd_ret);
    }else if (index != 0){ // read from previous cmd
        // pipe1(fd);
        // std::cout << "not 0" << std::endl;

        close(prev[1]);
        dup2(prev[0],STDIN_FILENO); // read from prev pipe
        close(prev[0]);
    }
    close(cur[0]);
    dup2(cur[1], STDOUT_FILENO); //write to cur pipe
    close(cur[1]);
    

    // ============ run command ======== //
    int err = execvp(argsu[0], argsu);
    std::cerr << "Process creation failed. error: " << strerror(errno) << std::endl;

    if (err == -1)
    {
        exit(0);
    }
    return NULL;
}

void *Parent(std::list<Command> *commands, int index, int pid){
    auto it = commands->begin();
    auto cmd = std::next(it, index);
    std::string outfile = cmd -> output_file;

    int status;
    char buff[1024];
    char newbuff[1024];

    if(index != 0){  // dont need prev in parent
        close(prev[0]);
        close(prev[1]);
    }
    if(index != commands->size() - 1){ // sets previous pipe to current pipe
        prev[0] = cur[0];
        prev[1] = cur[1];
    }
    
    int Wret = waitpid(pid, &status, 0);
    if(Wret == -1 ){
        std::cerr << "Process waitpit() failed. error: " << strerror(errno) << std::endl;
    }

    // close(cur[1]);

    if (cmd -> input_file.empty() && !(cmd -> output_file).empty()){ 
        // dettermine if there is a file to write to (detemine outfile exits)
        // std::cout << "In output loop";
        int fd_ret = open(cmd->output_file.c_str(),O_WRONLY | O_CREAT, 0666);
        if(fd_ret < 0){
            std::cerr << "Failed to open file " << cmd->output_file << ". error:" << strerror(errno) << std::endl;
            kill(pid, SIGKILL);
            return NULL;
        }

        int ret = read(cur[0], buff, 1024); // read from cur[0] pipe
        write(fd_ret, buff, ret); // write to file
        close(fd_ret);

    }else if(index == commands->size() - 1){ // if last command write to STDOUT_FILENO
        int ret = read(cur[0], newbuff, 1024);
        write(stdfd[1], newbuff, ret);
    }

    // close(cur[0]);


    return NULL;
}

int main(int args, char **argv){

    struct stat status;
    fstat(STDIN_FILENO, &status);
    std::string input;
    stdfd[0] = dup(STDIN_FILENO);
    stdfd[1] = dup(STDOUT_FILENO);
    // Display a character to show the user we are in an active shell.
    if (S_ISCHR(status.st_mode))
        std::cout << "? ";

    // Pipe files or read from the user prompt
    // TODO: Groups will need to swap out getline() to detect the tab character.
    while (getline(std::cin, input)){

        std::cout << std::endl;

        // Add another case here if you are in a group to handle \t!
        if (input == "exit")
        {
            return 1;
        }
        else
        {
            // TODO: Put your command execution logic here
            
            std::list<Command> *commandsList = Parser::Parse(input); // grab the commands inputed
            for (int x = 0; x < commandsList->size(); x++) // cycle through commands and fork for each cmd
            {
                pipe(cur);
                int pid = fork();
                // std::cout << "first " << pid << std::endl;
                if (pid == 0)
                {
                    // you are the child
                    // std::cout << "Going into child" << std::endl;
                    Child(commandsList, x);
                    return 1;
                }
                else if (pid > 0){
                    // you are the parent
                    // std::cout << "Going into Parent" << std::endl;
                    Parent(commandsList, x, pid);
                }else if(pid < 0 ){
                    std::cout << "Process fork failed. error: " << std::endl;
                    exit(1);
                }
            } 
            }
        std::cout << std::endl;
        // Display a character to show the user we are in an active shell.
        if (S_ISCHR(status.st_mode))
            std::cout << "? ";
        dup2(stdfd[0], STDIN_FILENO);
    }
}
