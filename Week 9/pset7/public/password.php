<?php

    // configuration
    require("../includes/config.php");
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       // validate submission
       // check if fields are empty
       if (empty($_POST["password"]) || empty($_POST["confirmation"]))
       {
            apologize("Please complete the form");
       }
       else
       {
            // check if confirmation is correct
            if ($_POST["password"] != $_POST["confirmation"])
            {
                apologize("Passwords does not match!");
            }
            
            // check if new password is same as old password
            $oriPassword = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"])[0]["hash"];
            if (crypt($_POST["password"], $oriPassword) == $oriPassword)
            {
                apologize("Password is the same as old password.");
            }
       }
       
       // update password
       query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]);
       redirect("/");
    }
    else
    {
        // render buy form
        render("password_form.php", ["title" => "Change password"]);
    }

?>
