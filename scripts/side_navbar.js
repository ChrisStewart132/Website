/*
    <div id=home>home at top of page</div>
    <div class="sideNavBar">
        <a href="#home">HOME</a>
        <a href="#section1">section1</a>
        <a href="#section2">section2</a>
    </div>
    <main>
        <div id="section1">
            section1
        </div>
        <div id="section2">
            section2 etc
        </div>
    </main>

*/

// Function to throttle events
function throttle(callback, delay) {
    let timeoutId;
    let lastExecTime = 0;
    return function() {
        const context = this;
        const args = arguments;
        const currentTime = new Date().getTime();
        const throttledFunction = function() {
            lastExecTime = currentTime;
            callback.apply(context, args);
        };
        if (currentTime >= lastExecTime + delay) {
            clearTimeout(timeoutId);
            throttledFunction();
        } else {
            clearTimeout(timeoutId);
            timeoutId = setTimeout(throttledFunction, delay);
        }
    };
}


function updateSideNavbar() {
    const navLinks = document.querySelectorAll('.sideNavBar > a ');
    // Function to update the active link
    function updateActiveLink() {
        const sections = Array.from(document.querySelector('main').children)
        const scrollPosition = window.scrollY;
        sections.forEach(section => 
        {
            const sectionTop = section.offsetTop;
            const sectionHeight = section.clientHeight;
            if (scrollPosition >= sectionTop - 100 && scrollPosition < sectionTop + sectionHeight + 300) {
                const targetId = section.getAttribute('id');
                navLinks.forEach(link => {
                if (link.getAttribute('href') === `#${targetId}`) {
                    link.classList.add('active');
                } else {
                    link.classList.remove('active');
                }
                });
            }
        });
        if(scrollPosition < 100){
            navLinks.forEach(link => {
                link.classList.remove('active');
            })
            document.querySelector(".sideNavBar").children[0].classList.add('active');
        }else{
            document.querySelector(".sideNavBar").children[0].classList.remove('active');
        }
    }

    // Throttle the updateActiveLink function to run every x milliseconds
    const throttledUpdateActiveLink = throttle(updateActiveLink, 33);


    // Call updateActiveLink when the page loads and on scroll
    window.addEventListener('scroll', throttledUpdateActiveLink);
    throttledUpdateActiveLink();
}


// side navbar
document.addEventListener('DOMContentLoaded', updateSideNavbar);
document.querySelector(".sideNavBar").children[0].classList.add('active');