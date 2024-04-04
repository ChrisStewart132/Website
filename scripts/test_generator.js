// test generator
updateDimensions(document.getElementById("testDimensions"))
function updateDimensions(input){
    const container = (document.querySelector(".test")).querySelector(".dimensions")
    let currentDimensions = container.children.length
    const targetDimensions = parseInt(input.value);
    const dimensionElement = container.children[0];// 1 child will always exist
    while(container.children.length < targetDimensions){
        const clonedDimension = dimensionElement.cloneNode(true);
        container.append(clonedDimension);
    }
    while(container.children.length > targetDimensions){
        const lastChild = container.children[container.children.length-1];
        container.removeChild(lastChild);
    }
}
function getRandomInt(min, max) {
    return Math.round(Math.random() * (max - min)) + min;
}
function getRandomFloat(min, max) {
    return (Math.random() * (max - min)) + min;
}
function getRandomChar() {
    return String.fromCharCode(getRandomInt(97, 122));// lower case
}
function getRandomString(min, max){
    let s = "";
    const length = getRandomInt(min, max);
    for(let i = 0; i < length; i++){
        s += getRandomChar();
    }
    return s;
}
function testValue(min, max, type){
    if (type === "float" || type === "floatString"){
        return getRandomFloat(min, max);
    } else if(type === "char"){
        return getRandomChar();
    } else if(type === "string"){
        return getRandomString(min, max);
    } else {// int intString
        return getRandomInt(min, max);
    }    
}        
function generate(){
    const nDimensions = parseInt(document.getElementById("testDimensions").value);
    if(nDimensions > 1){
        generate2();
        return;
    }
    const p = document.getElementById("testResult");
    const length = parseInt(document.getElementById("testLength").value);

    const container = (document.querySelector(".test")).querySelector(".dimension");
    const options = container.querySelectorAll("input");
    const min = parseInt(options[0].value);
    const max = parseInt(options[1].value);
    const type = container.querySelector("select").value;
    
    let arr = [];
    for(let i = 0; i < length; i++){
        arr.push(testValue(min, max, type));      
    }
    let joinedString;
    if(type === "intString" || type === "char" ||type === "string"){
        joinedString = arr.map(str => `"${str}"`).join(",");
    } else if (type === "float") {
        joinedString = arr.map(float => float.toFixed(2)).join(",");
    }else if (type === "floatString") {
        joinedString = arr.map(float =>  `"${float.toFixed(2)}"`).join(",");
    } else if(type === "int"){
        joinedString = arr.map(int => `${int}`).join(",");
    }
    //p.textContent = "[" + joinedString + "]"
    updateElementText(p, "[" + joinedString + "]")
}
function generate2(){
    const nDimensions = parseInt(document.getElementById("testDimensions").value);
    const p = document.getElementById("testResult");
    const length = parseInt(document.getElementById("testLength").value);
    let arr = [];
    for(let i = 0; i < length; i++){
        let subArr = [];
        for(let j = 0; j < nDimensions; j++){
            const container = (document.querySelector(".test")).querySelector(".dimensions").children[j];
            const options = container.querySelectorAll("input");
            const min = parseInt(options[0].value);
            const max = parseInt(options[1].value);
            const type = container.querySelector("select").value; 
            subArr.push(testValue(min, max, type));   
        }
        arr.push(subArr);
    }
    let joinedString = "";
    for(let i = 0; i < length; i++){
        let subString = "";
        for(let j = 0; j < nDimensions; j++){
            let container = (document.querySelector(".test")).querySelector(".dimensions").children[j];
            let type = container.querySelector("select").value;  
            if(type === "intString" || type === "char" ||type === "string"){
                subString += `"${arr[i][j]}",`
            } else if (type === "float") {
                subString += arr[i][j].toFixed(2) + ","
            }else if (type === "floatString") {
                subString += `"${arr[i][j].toFixed(2)}",`;
            }else if(type === "int"){
                subString += arr[i][j] + ","
            }
        }
        subString = subString.slice(0, -1);// remove last ','
        joinedString += "[" + subString + "],";
    }
    joinedString = joinedString.slice(0, -1);// remove last ','
    //p.textContent = "[" + joinedString + "]"
    updateElementText(p, "[" + joinedString + "]")
}