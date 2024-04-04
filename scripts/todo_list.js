loadTasks(document.getElementById("todoList"))
function loadTasks(listElement){
    for (let i = 0; i < localStorage.length; i++) {
        const key = localStorage.key(i);
        const value = localStorage.getItem(key);
        if(value === "0" || value === "1"){
            addTask(key, listElement, false)
        }
    }
}
function addTask(taskString, listElement, reset=true){
    // create task checkbox
    const removeElement = document.createElement(`input`);
    removeElement.type = "checkbox";
    removeElement.value = "REMOVE";
    removeElement.onclick = function(){
        if(!this.checked){// clicking unchecks it then it can be deleted
            localStorage.setItem(taskString, "0")
            if(confirm("Remove task?")){
                const taskElement = this.parentElement.querySelector(`span`)
                localStorage.removeItem(taskString)
                this.parentElement.remove();
            }
        }else{
            localStorage.setItem(taskString, "1")
        }
    };
    // create task text
    const taskElement = document.createElement(`span`);
    taskElement.textContent = taskString;
    taskElement.style.margin = "30px"
    // create/append task container with its childen to the task list
    const divElement = document.createElement(`div`);
    divElement.style.textAlign = "left"
    divElement.style.marginLeft = "33%"
    divElement.append(removeElement)
    divElement.append(taskElement)
    listElement.append(divElement)

    document.getElementById("todoInput").value = ""
    if(reset)
        localStorage.setItem(taskString, "0")
    else{
        removeElement.checked = localStorage.getItem(taskString) === "1"
    }

}