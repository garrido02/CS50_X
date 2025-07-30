
// Elements that depend on content loaded
document.addEventListener('DOMContentLoaded', function(){
    //1. Autoselect "iniciante" for the workout part
    document.getElementById("myLink").click();
});


// Function Defining Section

//1. Tabbed Menu defining
function openMenu(evt, menuName) {
    var i, x, tablinks;
    x = document.getElementsByClassName("menu");
    for (i = 0; i < x.length; i++) {
    x[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablink");
    for (i = 0; i < x.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" w3-black", "");
    }
    document.getElementById(menuName).style.display = "block";
    evt.currentTarget.firstElementChild.className += " w3-black";
}

//2. Defining sendMail
function sendMail(){
    var yourMessage = document.getElementById("message").value;
    var subject = document.getElementById("subject").value;
    location.href = "mailto:maxyourworkout@gmail.com?subject="
    +encodeURIComponent(subject)
    +"&body="+ encodeURIComponent(yourMessage);
}

//3. Toggle between showing and hiding the sidebar when clicking the menu icon
function w3_open() {
    var mySidebar = document.getElementById("mySidebar");
    if (mySidebar.style.display === 'block') {
        mySidebar.style.display = 'none';
    } else {
        mySidebar.style.display = 'block';
    }
}

//4. Close the sidebar with the close button
function w3_close() {
mySidebar.style.display = "none";
}

//5. Open packet page depending on clicked packet
function openPage(pack_name){
    location.href="https://garrido02-shiny-orbit-44px74vgxwjfqxp4-5000.preview.app.github.dev/"
    +pack_name;
}

//6. redirect to instagram in both instgram icons
function instagram(){
    location.href="https://www.instagram.com/maxyourworkout/?theme=dark";
}

//7. redirect to trainers instagram depending on who they click on
function trainer(trainerLink){
   location.href="https://www.instagram.com/"
   +trainerLink
   +"/?theme=dark";
}

//8. redirect to sub page depending on sub button
function sub(subLink){
    location.href="https://garrido02-shiny-orbit-44px74vgxwjfqxp4-5000.preview.app.github.dev/"
    +subLink;
}

//9. redirect to page to buy
function buyPack(pack_name){
    location.href="https://garrido02-shiny-orbit-44px74vgxwjfqxp4-5000.preview.app.github.dev/"
    +pack_name
    +"/buy";
}

//10. redirect to app instalation
function app_install(fitr_code){
    location.href="https://app.fitr.training/plan/"
    +fitr_code
    +"/purchase?";
}

//11. navbar scroll hide
var prevScrollpos = window.pageYOffset;
window.onscroll = function() {
var currentScrollPos = window.pageYOffset;
if (prevScrollpos > currentScrollPos) {
    document.getElementById("navbar").style.top = "0";
} else {
    document.getElementById("navbar").style.top = "-100px";
}
prevScrollpos = currentScrollPos;
}