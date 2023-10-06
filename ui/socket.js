const OUTPUT_CODE = {
  NONE: 0,
  DIMENSIONS: 1,
  MOUSE_POSITION: 2,
  MOUSE_CLICK: 3,
  IMAGE_LOADED: 4,
  SOUND_LOADED: 5
}

const INPUT_CODE = {
  NONE: 0,
  UPDATE_MOUSE_POSITION: 1,
  TRACK_MOUSE_CLICK: 2,
  CTX_COMMAND: 3,
  LOAD_IMAGE: 4,
  SET_BACKGROUND_COLOR: 5,
  SET_CURSOR: 6,
  ADD_SOUND: 7,
  PLAY_SOUND: 8,
  PAUSE_SOUND: 9
}

const images = {};
const sounds = {};

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let socket = null;

function sendToServer(object) {
  if (socket != null && socket.readyState == 1) {
    socket.send(JSON.stringify(object));
  }
}

function handleWebSocketMessage(event) {
  console.log('Message from server:', event.data);
  const obj = JSON.parse(event.data);
  if (obj.code == INPUT_CODE.CTX_COMMAND) {
    eval?.(`"use strict";${obj.command}`);

  } else if (obj.code == INPUT_CODE.UPDATE_MOUSE_POSITION) {
    if (obj.update == true) {
      canvas.addEventListener("mousemove", trackMousePosition);
    } else {
      canvas.removeEventListener("mousemove", trackMousePosition);
    }

  } else if (obj.code == INPUT_CODE.TRACK_MOUSE_CLICK) {
    if (obj.track == true) {
      canvas.addEventListener("click", trackMouseClick);
    } else {
      canvas.removeEventListener("click", trackMouseClick);
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

  }
}

function sendSoundLoaded(name) {
  if (socket != null && socket.readyState == 1) {
    soundLoaded = {
      "code": OUTPUT_CODE.SOUND_LOADED,
      "name": name
    }
    sendToServer(soundLoaded);
  }
}

function sendImageLoaded(name) {
  if (socket != null && socket.readyState == 1) {
    imageLoaded = {
      "code": OUTPUT_CODE.IMAGE_LOADED,
      "name": name
    }
    sendToServer(imageLoaded);
  }
}

function trackMouseClick(event) {
  if (socket != null && socket.readyState == 1) {
    mouseClick = {
      "code": OUTPUT_CODE.MOUSE_CLICK,
      "x": event.clientX,
      "y": event.clientY
    }
    sendToServer(mouseClick);
  }
}

function trackMousePosition(event) {
  if (socket != null && socket.readyState == 1) {
    mousePosition = {
      "code": OUTPUT_CODE.MOUSE_POSITION,
      "x": event.clientX,
      "y": event.clientY
    }
    sendToServer(mousePosition);
  }
}

function adjustCanvasSize() {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
  if (socket != null && socket.readyState == 1) {
    dimensions = {
      "code": OUTPUT_CODE.DIMENSIONS,
      "width": canvas.width,
      "height": canvas.height
    }
    sendToServer(dimensions);
  }
}

window.addEventListener("resize", adjustCanvasSize);

window.addEventListener("beforeunload", (event) => {
  if (socket != null && socket.readyState == 1) {
    socket.close();
  }
});

function connectWebSocket() {
  socket = new WebSocket("ws://localhost:65000");

  socket.addEventListener('open', (event) => {
    console.log('WebSocket connection opened:', event);

    socket.addEventListener('message', handleWebSocketMessage);

    adjustCanvasSize();
  });

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
