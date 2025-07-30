import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import string
import sys


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 library to use SQlite database
db = SQL("sqlite:///database.db")

# import special characters
punct = string.punctuation
PUNCT = []
for i in punct:
    PUNCT.append(i)

@app.after_request
def after_request(response):
    """Ensure responses are not cashed"""
    response.headers["Cache-Control"] = "no-chache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    """Ensure user gets back to index after post on main page (send message)"""
    if request.method == "GET":
        # select portfolio of packs available
        pack = db.execute("SELECT * FROM pack")

        # select members of team available
        team1 = db.execute("SELECT * FROM team WHERE short = ?", "joana")
        team2 = db.execute("SELECT * FROM team WHERE short = ?", "sergio")

        # select sub available
        sub1 = db.execute("SELECT * FROM sub WHERE id = ?", 1)
        sub2 = db.execute("SELECT * FROM sub WHERE id = ?", 2)
        sub3 = db.execute("SELECT * FROM sub WHERE id = ?", 3)

        # select workout
        
        workout_f = db.execute("SELECT nivel, description, name FROM workout JOIN workout_exercise_descriptions ON workout_exercise_descriptions.id_workout = workout.id JOIN exercise_descriptions ON exercise_descriptions.id = workout_exercise_descriptions.id_description JOIN exercise ON exercise.id = workout_exercise_descriptions.id_exercise WHERE nivel = ?", "Iniciado")
        workout_h = db.execute("SELECT nivel, description, name FROM workout JOIN workout_exercise_descriptions ON workout_exercise_descriptions.id_workout = workout.id JOIN exercise_descriptions ON exercise_descriptions.id = workout_exercise_descriptions.id_description JOIN exercise ON exercise.id = workout_exercise_descriptions.id_exercise WHERE nivel = ?", "Avançado")

        return render_template("index.html", pack=pack, workout_f=workout_f, team1=team1, team2 = team2, workout_h=workout_h, sub1=sub1, sub2=sub2, sub3=sub3)

    else:
        return redirect("/")


@app.route("/casa")
def casa():
    """Ensure users gets back to main page after submit any info on this page"""
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Casa 30'")
    return render_template("pacotes.html", pack=pack)


@app.route("/casa-material")
def casa_material():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Casa c/Pesos 30'")
    return render_template("pacotes.html", pack=pack)


@app.route("/saude")
def saude():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Saúde e Bem-Estar")
    return render_template("pacotes.html", pack=pack)


@app.route("/gravidas")
def gravidas():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Grávidas")
    return render_template("pacotes.html", pack=pack)


@app.route("/funcional-60")
def funcional_60():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Funcional 60'")
    return render_template("pacotes.html", pack=pack)


@app.route("/funcional-30")
def funcional_30():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Funcional 30'")
    return render_template("pacotes.html", pack=pack)



@app.route("/pernas-gluteos")
def pernas_gluteos():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Pernas e Glúteos")
    return render_template("pacotes.html", pack=pack)


@app.route("/squat")
def squat():
    # select pack
    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Front & Back Squat")
    return render_template("pacotes.html", pack=pack)


#@app.route("/teste")
#def teste():
#    pack = db.execute("SELECT * FROM pack WHERE name = ?", "Funcional 60")
#    print(pack)
#    return render_template("layout_pacote.html", pack=pack)