<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // make sure password and confirmation aren't blank
        if (!empty($_POST["password"]) && !empty($_POST["confirmation"]))
        {
            // make sure password and confirmation are the same
            if ($_POST["password"] == $_POST["confirmation"])
            {
                // make sure username is not blank
                if (!empty($_POST["username"]))
                {
                    $result = query("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000.0000)", $_POST["username"], crypt($_POST["password"]));
                    // unable to insert, must be duplicate username
                    if ($result === false)
                    {
                        apologize("Username has been taken.");
                    }
                    // if successfully inserted
                    else
                    {
                        // log them in
                        // store their id in session
                        $row = query("SELECT LAST_INSERT_ID() as id");
                        $id = $row[0]["id"];
                        $_SESSION[$id];
                        redirect("/");
                    }
                }
                else
                {
                    apologize("Please enter a username.");
                }
            }
            else
            {
                apologize("Passwords do not match!");
            }
        }
        else
        {
            apologize("You must provide password.");
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
