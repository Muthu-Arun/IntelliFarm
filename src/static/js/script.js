// Selecting DOM elements
const wrapper = document.querySelector('.wrapper');
const loginLink = document.querySelector('.loginLink');
const registerLink = document.querySelector('.register-link');
const btnLoginPopup = document.querySelector('.btnLogin-popup');
const popupContainer = document.getElementById('popup-container');
const closePopup = document.getElementById('close-popup');
const circle = document.getElementById('circle');

// Check if elements are found before adding event listeners
if (registerLink && loginLink && btnLoginPopup && popupContainer && closePopup) {
    registerLink.addEventListener('click', () => {
        wrapper.classList.add('active');
    });

    loginLink.addEventListener('click', () => {
        wrapper.classList.remove('active');
    });

    btnLoginPopup.addEventListener('click', () => {
        popupContainer.style.display = 'flex'; // Show the popup
    });

    closePopup.addEventListener('click', () => {
        popupContainer.style.display = 'none'; // Hide the popup
    });
}

// Initialize Kinet if circle element is present
if (circle) {
    var kinet = new Kinet({
        acceleration: 0.02,
        friction: 0.25,
        names: ["x", "y"],
    });

    kinet.on('tick', function(instances) {
        circle.style.transform = `translate3d(${instances.x.current}px, ${instances.y.current}px, 0) rotateX(${instances.x.velocity / 2}deg) rotateY(${instances.y.velocity / 2}deg)`;
    });

    document.addEventListener('mousemove', function (event) {
        kinet.animate('x', event.clientX - window.innerWidth / 2);
        kinet.animate('y', event.clientY - window.innerHeight / 2);
    });

    kinet.on('start', function() {
        console.log('start');
    });

    kinet.on('end', function() {
        console.log('end');
    });
}
