document.addEventListener('DOMContentLoaded', function() {

        let about = document.querySelector("#about");
        about.addEventListener('click', function(about){
            window.location.href="about.html";
        })

        let academic = document.querySelector("#academic");
        academic.addEventListener('click', function(academic){
            window.location.href='academic.html';
        })

        let future = document.querySelector("#future");
        future.addEventListener('click', function(future){
            window.location.href='future.html';
        })

    });