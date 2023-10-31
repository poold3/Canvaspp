const OUTPUT_CODE = {
  NONE: 0,
  DIMENSIONS: 1,
  MOUSE_POSITION: 2,
  MOUSE_DOWN: 3,
  MOUSE_UP: 4,
  IMAGE_LOADED: 5,
  SOUND_LOADED: 6,
  KEY_DOWN: 7,
  KEY_UP: 8,
  MEASURED_TEXT: 9,
  PROMPT_RESPONSE: 10,
  CONFIRM_RESPONSE: 11
}

const INPUT_CODE = {
  NONE: 0,
  TRACK_MOUSE_POSITION: 1,
  TRACK_MOUSE_CLICK: 2,
  CTX_COMMAND: 3,
  LOAD_IMAGE: 4,
  SET_BACKGROUND_COLOR: 5,
  SET_CURSOR: 6,
  ADD_SOUND: 7,
  PLAY_SOUND: 8,
  PAUSE_SOUND: 9,
  TRACK_KEY_PRESS: 10,
  MEASURE_TEXT: 11,
  ALERT: 12,
  SET_TITLE: 13,
  SET_FAVICON: 14,
  PROMPT: 15,
  CONFIRM: 16
}

const animationQueue = {
  queue: new Array(),
  push: function(command) {
    this.queue.push(command);
    if (this.queue.length >= 5) {
      this.queue.splice(0, this.queue.length - 2);
    }
  },
  getNext: function() {
    return this.queue.shift();
  }
}

const images = {};
const sounds = {};
const keysDown = {};

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const title = document.getElementById("title");
const favicon = document.getElementById("favicon");
let socket = null;

// Send a json string to the server.
function sendToServer(object) {
  if (socket != null && socket.readyState == 1) {
    socket.send(JSON.stringify(object));
  }
}

// The step function used in requestAnimationFrame
function animationStep() {
  const command = animationQueue.getNext();
  if (command) {
    const commandFunction = new Function(command);
    commandFunction();
  }
  window.requestAnimationFrame(animationStep);
}

// Handle messages/commands from the server.
function handleWebSocketMessage(event) {
  const obj = JSON.parse(event.data);
  if (obj.code == INPUT_CODE.CTX_COMMAND) {
    animationQueue.push(obj.command);
    
  } else if (obj.code == INPUT_CODE.TRACK_MOUSE_POSITION) {
    if (obj.track == true) {
      canvas.addEventListener("mousemove", trackMousePosition);
    } else {
      canvas.removeEventListener("mousemove", trackMousePosition);
    }

  } else if (obj.code == INPUT_CODE.TRACK_MOUSE_CLICK) {
    if (obj.track == true) {
      canvas.addEventListener("mousedown", trackMouseDown);
      canvas.addEventListener("mouseup", trackMouseUp);
    } else {
      canvas.removeEventListener("mousedown", trackMouseDown);
      canvas.removeEventListener("mouseup", trackMouseUp);
    }

  } else if (obj.code == INPUT_CODE.LOAD_IMAGE) {
    const img = new Image();
    img.src = obj.src;
    img.addEventListener("load", (event) => {
      sendImageLoaded(obj.name);
    });
    images[obj.name] = img;

  } else if (obj.code == INPUT_CODE.SET_BACKGROUND_COLOR) {
    canvas.style.backgroundColor = obj.color;

  } else if (obj.code == INPUT_CODE.SET_CURSOR) {
    canvas.style.cursor = obj.cursor;

  } else if (obj.code == INPUT_CODE.ADD_SOUND) {
    const newSound = document.createElement("audio");
    if (newSound.canPlayType("audio/mpeg")) {
      function eventHandler() {
        sendSoundLoaded(obj.name);
        newSound.removeEventListener("canplaythrough", eventHandler);
      }
      newSound.addEventListener("canplaythrough", eventHandler);
      newSound.setAttribute("preload", "auto");
      newSound.setAttribute("src", obj.src);
      newSound.volume = obj.volume;
      newSound.playbackRate = obj.playbackRate;
      if (obj.loop) {
        newSound.setAttribute("loop", "true");
      }
      sounds[obj.name] = newSound;
    }

  } else if (obj.code == INPUT_CODE.PLAY_SOUND) {
    if (obj.startTime != -1) {
      sounds[obj.name].currentTime = obj.startTime;
    }
    sounds[obj.name].play();

  } else if (obj.code == INPUT_CODE.PAUSE_SOUND) {
    sounds[obj.name].pause();

  } else if (obj.code == INPUT_CODE.TRACK_KEY_PRESS) {
    if (obj.track == true) {
      document.addEventListener("keydown", trackKeyDown);
      document.addEventListener("keyup", trackKeyUp);
    } else {
      document.removeEventListener("keydown", trackKeyDown);
      document.removeEventListener("keyup", trackKeyUp);
    }
  } else if (obj.code == INPUT_CODE.MEASURE_TEXT) {
    measureText(obj.text);
  } else if (obj.code == INPUT_CODE.ALERT) {
    window.alert(obj.alert);
  } else if (obj.code == INPUT_CODE.SET_TITLE) {
    title.innerText = obj.title;
  } else if (obj.code == INPUT_CODE.SET_FAVICON) {
    favicon.href = obj.href;
  } else if (obj.code == INPUT_CODE.PROMPT) {
    sendPrompt(obj.key, obj.prompt);
  } else if (obj.code == INPUT_CODE.CONFIRM) {
    sendConfirm(obj.key, obj.message);
  }
}

// Performs a window.prompt() and sends the response to the server.
function sendPrompt(key, prompt) {
  if (socket != null && socket.readyState == 1) {
    const response = window.prompt(prompt);
    const promptResponse = {
      "code": OUTPUT_CODE.PROMPT_RESPONSE,
      "key": key,
      "response": response
    };
    sendToServer(promptResponse);
  }
}

// Performs a window.confirm() and sends the response to the server.
function sendConfirm(key, message) {
  if (socket != null && socket.readyState == 1) {
    const response = window.confirm(message);
    const confirmResponse = {
      "code": OUTPUT_CODE.CONFIRM_RESPONSE,
      "key": key,
      "response": response
    };
    sendToServer(confirmResponse);
  }
}

// Send a text measurement to the server.
function measureText(text) {
  if (socket != null && socket.readyState == 1) {
    const measurement = ctx.measureText(text).width;
    const measuredText = {
      "code": OUTPUT_CODE.MEASURED_TEXT,
      "text": text,
      "measurement": measurement
    };
    sendToServer(measuredText);
  }
}

// Send a key press to the server if the key is not already down.
function trackKeyDown(event) {
  if (socket != null && socket.readyState == 1 && (!Object.hasOwn(keysDown, event.code) || !keysDown[event.code])) {
    keysDown[event.code] = true;
    const keyPress = {
      "code": OUTPUT_CODE.KEY_DOWN,
      "pressCode": event.code,
    };
    sendToServer(keyPress);
  }
}

// Send a key press to the server if a key is released.
function trackKeyUp(event) {
  if (socket != null && socket.readyState == 1) {
    keysDown[event.code] = false;
    const keyPress = {
      "code": OUTPUT_CODE.KEY_UP,
      "pressCode": event.code,
    };
    sendToServer(keyPress);
  }
}

// Send confirmation to the server that a sound has loaded.
function sendSoundLoaded(name) {
  if (socket != null && socket.readyState == 1) {
    const soundLoaded = {
      "code": OUTPUT_CODE.SOUND_LOADED,
      "name": name
    };
    sendToServer(soundLoaded);
  }
}

// Send confirmation to the server that an image has loaded.
function sendImageLoaded(name) {
  if (socket != null && socket.readyState == 1) {
    const imageLoaded = {
      "code": OUTPUT_CODE.IMAGE_LOADED,
      "name": name
    };
    sendToServer(imageLoaded);
  }
}

// Send a mouse click to the server.
function trackMouseDown(event) {
  if (socket != null && socket.readyState == 1) {
    const mouseClick = {
      "code": OUTPUT_CODE.MOUSE_DOWN,
      "x": event.clientX,
      "y": event.clientY
    };
    sendToServer(mouseClick);
  }
}

// Send a mouse click to the server when the mouse click is released.
function trackMouseUp(event) {
  if (socket != null && socket.readyState == 1) {
    const mouseClick = {
      "code": OUTPUT_CODE.MOUSE_UP,
      "x": event.clientX,
      "y": event.clientY
    };
    sendToServer(mouseClick);
  }
}

// Send the current mouse position to the server.
function trackMousePosition(event) {
  if (socket != null && socket.readyState == 1) {
    const mousePosition = {
      "code": OUTPUT_CODE.MOUSE_POSITION,
      "x": event.clientX,
      "y": event.clientY
    };
    sendToServer(mousePosition);
  }
}

// Resize the canvas and send new size to the server.
function adjustCanvasSize() {
  console.log(window.innerWidth + 1);
  canvas.width = window.innerWidth + 1;
  canvas.height = window.innerHeight + 1;
  console.log(canvas.width);
  console.log(window.innerWidth);
  if (socket != null && socket.readyState == 1) {
    const dimensions = {
      "code": OUTPUT_CODE.DIMENSIONS,
      "width": canvas.width,
      "height": canvas.height
    };
    sendToServer(dimensions);
  }
}

// Add window resize listener to resize canvas.
window.addEventListener("resize", adjustCanvasSize);

// Close the socket connection before exiting.
window.addEventListener("beforeunload", (event) => {
  if (socket != null && socket.readyState == 1) {
    socket.close();
  }
});

// Initiate the websocket connection. Set the open, close, and error handlers.
function connectWebSocket() {
  socket = new WebSocket("ws://localhost:65000");

  socket.addEventListener('open', (event) => {
    console.log('WebSocket connection opened:', event);

    socket.addEventListener('message', handleWebSocketMessage);
    adjustCanvasSize();
    window.requestAnimationFrame(animationStep);
  });

  // Window will close if socket connection closes.
  socket.addEventListener('close', (event) => {
    console.log('WebSocket connection closed:', event);
    socket.removeEventListener('message', handleWebSocketMessage);
    socket = null;
    window.close();
  });

  socket.addEventListener('error', (event) => {
    console.error('WebSocket error:', event);
  });
}

connectWebSocket();
