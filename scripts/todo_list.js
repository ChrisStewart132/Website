const TASK_CHECKED_OPACITY = '0.5';
const TASK_UNCHECKED_OPACITY = '1.0';
const todoListElement = document.getElementById("todoList")
loadTasks(todoListElement)
loadDefaultTasks(todoListElement)
sortTasksByPriority(todoListElement)

function loadTasks(listElement){
    // tasks are mapped: taskString -> "0" (incomplete, or) "1" (for complete)
    for (let i = 0; i < localStorage.length; i++) {
        const key = localStorage.key(i);
        const value = localStorage.getItem(key);
        if(value === "0" || value === "1"){
            // addTask with reset=false loads an existing task from localStorage
                // reset=true creates a new task
            addTask(key, listElement, reset=false)
        }
    }
}
function sortTasksByPriority(listElement){
    // reads all the task divs into an array, sorts the arr, removes the tasks from the listElement,
        // and re-adds them from the arr in sorted order
    const priorities = ["taskDefaultPriority","taskLowPriority","taskMediumPriority","taskHighPriority"]
    let tasksArr = Array.from(listElement.children)
    tasksArr.sort((task1, task2)=>{
        const task1Str = task1.querySelector(`span`).textContent
        const task2Str = task2.querySelector(`span`).textContent
        const task1Prio = localStorage.getItem(task1Str+"priority")
        const task2Prio = localStorage.getItem(task2Str+"priority")
        return priorities.indexOf(task1Prio) < priorities.indexOf(task2Prio)
    })
    listElement.innerHTML = ""
    tasksArr.forEach(task => {
        return listElement.appendChild(task);
    })
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
            //this.parentElement.style.opacity = TASK_UNCHECKED_OPACITY;
            this.parentElement.classList.remove(`transparent`)
            if(confirm("Remove task?")){
                const taskElement = this.parentElement.querySelector(`span`)
                localStorage.removeItem(taskString)
                this.parentElement.remove();
            }
        }else{
            localStorage.setItem(taskString, "1")
            //this.parentElement.style.opacity = TASK_CHECKED_OPACITY;
            this.parentElement.classList.add(`transparent`)
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
        if(removeElement.checked){
            //divElement.style.opacity = TASK_UNCHECKED_OPACITY;
            divElement.classList.add(`transparent`)
        }else{
            divElement.classList.remove(`transparent`)
        }
        divElement.classList.add(localStorage.getItem(taskString + "priority"))
    }
}
function uncheckAllTasks(listElement){
    if(!confirm("Are you sure you want to un-check all tasks?")){
        return;
    }
    for(const taskDiv of listElement.children){
        const checkbox = taskDiv.querySelector(`input`)
        const taskStr = taskDiv.querySelector(`span`).textContent
        checkbox.checked = false;
        localStorage.setItem(taskStr, "0")
        //taskDiv.style.opacity = TASK_UNCHECKED_OPACITY;
        taskDiv.classList.remove(`transparent`)
      }
}
function removeAllTasks(listElement){
    if(!confirm("Are you sure you want to remove all tasks?")){
        return;
    }
    for(const taskDiv of listElement.children){  
        const taskStr = taskDiv.querySelector(`span`).textContent
        const taskPriortyStr = taskStr + "priority"
        console.log(taskStr)
        localStorage.removeItem(taskStr)// remove the tasks uncheck status
        localStorage.removeItem(taskPriortyStr)// remove the tasks priority status
    }
    while (listElement.firstChild) {
        listElement.removeChild(listElement.firstChild);
    }
}
function loadDefaultTasks(listElement){
    // only load default tasks if no tasks exist
    if(listElement.children.length > 0){
        return
    }
    // load some default tasks to show-case use
    addTask("click container to toggle priority", listElement)
    addTask("click checkbox once to check a task", listElement)
    addTask("click checkbox twice to prompt deletion", listElement)
    localStorage.setItem("example high priority task", `0`)
    localStorage.setItem("example high priority taskpriority", `taskHighPriority`)
    addTask("example high priority task", listElement, false)
}