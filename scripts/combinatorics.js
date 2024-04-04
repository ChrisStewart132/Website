// combinatorics
function variations(symbols, max_length, output, starting_candidate=""){
    let stack = [starting_candidate]
    while(stack.length > 0){
        let candidate = stack.pop()
        if(candidate.length > max_length){
            continue
        }
        output.push(candidate);
        for(let i = 0; i < symbols.length; i++){
            let child_candidate = candidate + symbols[i]
            stack.push(child_candidate)
        }
    }
}
function permutations(symbols, max_length, output, starting_candidate=""){
    let stack = [starting_candidate]
    while(stack.length > 0){
        let candidate = stack.pop()
        if(candidate.length > max_length){
            continue
        }
        output.push(candidate);
        for(let i = 0; i < symbols.length; i++){
            if(!candidate.includes(symbols[i])){
                let child_candidate = candidate + symbols[i]
                stack.push(child_candidate)
            }
        }
    }
}
function setsAreEqual(set1, set2) {
    if (set1.size !== set2.size) {
        return false;
    }
    for (let item of set1) {
        if (!set2.has(item)) {
            return false;
        }
    }
    return true;
}
function combinations(symbols, max_length, output, starting_candidate="") {
    let p = []
    permutations(symbols, max_length, p, starting_candidate)
    p.shift()
    for(const candidate of p){
        let s1 = new Set(candidate)
        let add = true
        for(const e of output){
            let s2 = new Set(e)
            console.log(s2)
            if(setsAreEqual(s1,s2)){
                add = false
                break
            }
        }
        if(add){
            output.push(candidate)
        }
    }
}
function generateCombinatorics(symbols, max_length, output, setting){
    let arr = [];
    if(setting == "variations"){
        variations(symbols, max_length, arr)
    }else if(setting == "permutations"){
        permutations(symbols, max_length, arr)
    }else if(setting == "combinations"){
        combinations(symbols, max_length, arr)
    }
    arr.shift(); // Removes the first empty element
    console.log(arr)
    //let joinedString = arr.toString();
    let joinedString = arr.map(str => `"${str}"`).join(",");
    updateElementText(output, "[" + joinedString + "]")
}