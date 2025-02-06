// PARTICLE TOKEN 

const deviceId = "REPLACE"; 
const accessToken = "REPLACE";

// MAIN PAGE //

function showDefinition(defId) {
    // Hide all definitions and remove active class from all tabs
    const definitions = document.querySelectorAll('.definition');
    definitions.forEach(def => def.classList.remove('active'));

    const tabs = document.querySelectorAll('.tab');
    tabs.forEach(tab => tab.classList.remove('active'));

    // Hide all images
    const images = document.querySelectorAll('.game-mode-image');
    images.forEach(img => img.style.opacity = 0); 

    // Show the selected definition
    document.getElementById(defId).classList.add('active');

    // Add active class to the clicked tab
    const activeTab = Array.from(tabs).find(tab =>
        tab.getAttribute('onclick') === `showDefinition('${defId}')`
    );
    if (activeTab) activeTab.classList.add('active');

    // Show the corresponding image if it exists
    const imageId = 'imageDef' + defId.charAt(defId.length - 1); 
    const activeImage = document.getElementById(imageId);
    if (activeImage) {
        activeImage.style.display = 'inline-block';  // Show the corresponding image
        setTimeout(() => {
            activeImage.style.opacity = 1;
        }, 10);
    }
}
function getRandomColor() { // Gets a random colr
    const randomNum = Math.floor(Math.random() * 3);
    if (randomNum === 0) {
        return `rgb(56, 113, 255)`; // Blue
    } else if (randomNum === 1) {
        return `rgb(242, 0, 56)`; // Red
    } else {
        return `rgb(48, 255, 20)`; // Green
    }
}

function startLEDAnimations() { // Used for led animations
    const leds = document.querySelectorAll('.led');
    let color = getRandomColor(); // get a random color
    let currentIndex = 0;

    function blink() { // Used to show the "LED" turning on and off
        let blinkCount = 0; 
        leds.forEach(led => led.style.backgroundColor = '#ccc');
        const blinkInterval = setInterval(() => {
            leds.forEach(led => led.style.backgroundColor = (blinkCount % 2 === 0) ? color : '#ccc');
            blinkCount++;
            if (blinkCount >= 6) {
                clearInterval(blinkInterval);
                setTimeout(() => {
                    color = getRandomColor(); 
                    animate(); 
                }, 1000); 
            }
        }, 350);
    }

    function animate() {
        leds.forEach(led => led.style.backgroundColor = '#ccc'); // Turn off all LEDs initially
        let step = 0;

        const normalInterval = setInterval(() => { //
            leds.forEach(led => led.style.backgroundColor = '#ccc'); // Turn off all LEDs
            leds[step].style.backgroundColor = color; // Turn on the LED with the current color
            step++;
            if (step >= leds.length) {
                clearInterval(normalInterval); 
                setTimeout(() => {
                    step = leds.length - 2;
                    const reverseInterval = setInterval(() => {
                        leds.forEach(led => led.style.backgroundColor = '#ccc'); 
                        leds[step].style.backgroundColor = color; 
                        step--;
                        if (step < 0) {
                            clearInterval(reverseInterval); 
                            setTimeout(() => {
                                blink();
                            }, 750); 
                        }
                    }, 750); 
                }, 0); 
            }
        }, 750);
    }
    animate(); 
}

window.onload = () => {
    startLEDAnimations();
    fetchHighScores();
};

// RANKINGS PAGE //

function fetchHighScores() {
    const activities = [
        { id: "mode1", variable: "most-MODE1-wins" },
        { id: "mode2", variable: "most-MODE2-wins" },
        { id: "mode4", variable: "most-MODE4-wins" },
        { id: "mode5", variable: "most-MODE5-wins" }
    ];

    activities.forEach(activity => {
        fetch(`https://api.particle.io/v1/devices/${deviceId}/${activity.variable}?access_token=${accessToken}`)
            .then(response => response.json())
            .then(data => {
                const element = document.getElementById(activity.id);
                if (element) {
                    element.innerText = data.result !== undefined ? data.result : "N/A";
                } else {
                    console.error(`Error: Element with ID '${activity.id}' not found.`);
                }
            })
            .catch(error => {
                console.error(`Error fetching ${activity.variable}:`, error);
                const element = document.getElementById(activity.id);
                if (element) element.innerText = "Error";
            });
    });
}
function docommand(endpoint, command) {
    fetch(`https://api.particle.io/v1/devices/${deviceId}/${endpoint}`, {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: `access_token=${accessToken}&args=${command}`
    }).then(response => {
        if (response.ok) console.log(`${endpoint} command sent successfully!`);
    }).catch(error => console.error(`Error sending ${endpoint} command:`, error));
}

// LED_CHANGER PAGE //


// Get references to the sliders and the LED
const redSlider = document.getElementById('red');
const greenSlider = document.getElementById('green');
const blueSlider = document.getElementById('blue');
const led = document.getElementById('led-changer');

// Update the LED color
function updateLEDColor() {
    const red = redSlider.value;
    const green = greenSlider.value;
    const blue = blueSlider.value;
    led.style.backgroundColor = `rgb(${red}, ${green}, ${blue})`;
}

// Add event listeners to the sliders
redSlider.addEventListener('input', updateLEDColor);
greenSlider.addEventListener('input', updateLEDColor);
blueSlider.addEventListener('input', updateLEDColor);

function sendRGBToPhoton() {
    const red = redSlider.value;
    const green = greenSlider.value;
    const blue = blueSlider.value;
    docommand("setRGB", `${red},${green},${blue}`);
}

sendButton.addEventListener('click', sendRGBToPhoton);
sendButton.addEventListener('click', fetchHighScores);

fetchHighScores();
updateLEDColor();