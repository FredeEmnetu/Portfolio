function textarea(num){
    document.getElementById("text").value = document.getElementById("text").value + num
}
function clear(){
    document.getElementById("button").innerHTML= " ";
}
function equal(){
    let old = document.getElementById("text").value;
    let arr = old.split(' ');
    if(arr[1] == "+"){
        document.getElementById("text").value = Number(arr[0]) + Number(arr[2])
    }
    if(arr[1] == "-"){
        document.getElementById("text").value = Number(arr[0]) - Number(arr[2])
    }if(arr[1] == "*"){
        document.getElementById("text").value = Number(arr[0]) * Number(arr[2])
    }  
}
function conversion(){
    // document.getElementsById("text").value = 
    let num = getElementById("")
}