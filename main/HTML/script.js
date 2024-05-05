function setSettings(){
    var xhttp = new XMLHttpRequest();
        xhttp.open("POST", "setSettings", true);
        xhttp.setRequestHeader('Content-Type', 'application/json');
        xhttp.send(JSON.stringify({
            SSID: document.getElementById("SSID").value,
            PASSWORD: document.getElementById("PASSWORD").value,
            delay: document.getElementById("delay").value,
            API_KEY: document.getElementById("API_KEY").value,
            }));
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4) {
                var response = JSON.parse(this.responseText);
                console.log(response);
                if (response.status == 200) {
                    alert('Settings uploaded');
                } else {
                    alert('Settings are not uploaded');
                }
            }
        }
}

function getSettings() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "getSettings", true);
    xhttp.send();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4) {
            var settings = JSON.parse(this.responseText);
            console.log(settings);
            document.getElementById("SSID").setAttribute('value', (settings.hasOwnProperty('SSID') > 0 ? settings.SSID : ""));
            document.getElementById("PASSWORD").setAttribute('value', (settings.hasOwnProperty('PASSWORD') > 0 ? settings.PASSWORD : ""));
            document.getElementById("delay").setAttribute('value', (settings.hasOwnProperty('delay') > 0 ? settings.delay : ""));
            document.getElementById("API_KEY").setAttribute('value', (settings.hasOwnProperty('API_KEY') > 0 ? settings.API_KEY : ""));
        }
    }
}

getSettings();