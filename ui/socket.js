const OUTPUT_CODE = {
  NONE: 0,
  DIMENSIONS: 1,
  MOUSE_POSITION: 2,
  MOUSE_CLICK: 3
}

const INPUT_CODE = {
  NONE: 0,
  TOGGLE_MOUSE_POSITION_TRANSMISSION: 1,
  TRACK_MOUSE_CLICK: 2
}

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
  if (obj.code == INPUT_CODE.TOGGLE_MOUSE_POSITION_TRANSMISSION) {
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
