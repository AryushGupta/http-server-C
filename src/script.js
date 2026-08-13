const input = document.getElementById("messageInput");
const sendButton = document.getElementById("sendButton");
const chatBox = document.getElementById("chatBox");
const messageContainer = document.getElementById("message-container");

function sendMessage(){
    const text = input.value.trim();
    // checking for empty message
    if(text === ""){
        return;
    }

    const newMessage = document.createElement("div");
    newMessage.classList.add("message", "receiver-message");

    const senderLogo = document.createElement("img");
    senderLogo.src = "https://media.geeksforgeeks.org/wp-content/uploads/20210511160813/g4g.jpg";
    senderLogo.alt = "avatar";
    senderLogo.classList.add("avatar");

    newMessage.appendChild(senderLogo);

    newMessage.appendChild(document.createTextNode(text));

    messageContainer.appendChild(newMessage);
    
    input.value = "";
    input.focus();

    console.log("Clicked");
    console.log(messageContainer);
}

sendButton.addEventListener("click", sendMessage);