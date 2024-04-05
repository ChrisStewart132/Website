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
    removeElement.className = "checkbox"
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
    taskElement.style.margin = "10px"
    // create/append task container with its childen to the task list
    const divElement = document.createElement(`div`);
    divElement.onclick = function(event){
        if(event.target.type == "checkbox"){
            return;
        }
        const taskString = this.querySelector(`span`).textContent
        const taskPriorityString = taskString + "priority"
        if(this.classList.contains(`taskDefaultPriority`)){
            this.classList.remove(`taskDefaultPriority`);
            this.classList.add(`taskLowPriority`);
            localStorage.setItem(taskPriorityString, "taskLowPriority")
        }
        else if(this.classList.contains(`taskLowPriority`)){
            this.classList.remove(`taskLowPriority`);
            this.classList.add(`taskMediumPriority`);
            localStorage.setItem(taskPriorityString, "taskMediumPriority")
        }
        else if(this.classList.contains(`taskMediumPriority`)){
            this.classList.remove(`taskMediumPriority`);
            this.classList.add(`taskHighPriority`);
            localStorage.setItem(taskPriorityString, "taskHighPriority")
        }
        else if(this.classList.contains(`taskHighPriority`)){
            this.classList.remove(`taskHighPriority`);
            this.classList.add(`taskDefaultPriority`);
            localStorage.setItem(taskPriorityString, "taskDefaultPriority")
        }
    }
    divElement.classList.add("task")
    divElement.append(removeElement)
    divElement.append(taskElement)
    listElement.append(divElement)

    // reset input
    document.getElementById("todoInput").value = ""
    // creating a new task
    if(reset){
        divElement.classList.add(`taskDefaultPriority`);
        localStorage.setItem(taskString, "0")
        localStorage.setItem(taskString + "priority", "taskDefaultPriority")
    }else{// loading a cached task
        removeElement.checked = localStorage.getItem(taskString) === "1"
        divElement.classList.add(localStorage.getItem(taskString + "priority"))
    }

}
function uncheckAll(listElement){
    if(!confirm("Are you sure you want to un-check all tasks?")){
        return;
    }
    for(const taskDiv of listElement.children){
        const checkbox = taskDiv.querySelector(`input`)
        const taskStr = taskDiv.querySelector(`span`).textContent
        checkbox.checked = false;
        localStorage.setItem(taskStr, "0")
      }
}