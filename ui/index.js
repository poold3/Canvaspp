const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

function adjustCanvasSize() {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
}

window.addEventListener("resize", adjustCanvasSize);

adjustCanvasSize();


let socket = null;

function connectWebSocket() {
  socket = new WebSocket("ws://localhost:65000");

  socket.addEventListener('open', (event) => {
    console.log('WebSocket connection opened:', event);

    socket.addEventListener('message', handleWebSocketMessage);
  });

  socket.addEventListener('close', (event) => {
    console.log('WebSocket connection closed:', event);

    socket.removeEventListener('message', handleWebSocketMessage);

    //setTimeout(connectWebSocket, 2000); // Retry every 2 seconds
  });

  socket.addEventListener('error', (event) => {
    console.error('WebSocket error:', event);
  });
}

function handleWebSocketMessage(event) {
  console.log('Message from server:', event.data);
}

connectWebSocket();
