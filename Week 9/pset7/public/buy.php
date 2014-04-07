<?php

    // configuration
    require("../includes/config.php");
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        // if symbol and number of shares is not filled
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("Form is not complete.");
        }
        
        // if number of shares is not non-negative integer
        if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Number of shares must be a non-negative integer.");
        }
        
        // if symbol does not exist
        if (lookup($_POST["symbol"]) === false)
        {
            apologize("Wrong symbol.");
        }
        
        // make symbol to uppercase
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"];
        $price = lookup($_POST["symbol"])["price"];
        // if user cannot afford the cash
        if ($cash - $price * $_POST["shares"] < 0)
        {
            apologize("You do not have enough money to buy the stock.");   
        }
        else
        {
            // add stock to portfolio
            query("INSERT INTO portfolios (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $_POST["shares"]);
            
            // update user's cash
            query("UPDATE users SET cash = cash - ? * ? WHERE id = ?", $price, $_POST["shares"], $_SESSION["id"]);
            
            // add history
            query("INSERT INTO history (id, action, symbol, shares, price) VALUES(?, 'BUY', ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $price);
            
            redirect("/");
        }
        
    }
    else
    {
        // render buy form
        render("buy_form.php", ["title" => "Buy form"]);
    }

?>
