<?php

    // configuration
    require("../includes/config.php");
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        $stock = query("SELECT * FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        // if user does not have the stock
        if (empty($stock))
        {
            apologize("You do not have the stock.");
        }
        // else sell the stock
        else
        {
            // get price of one share
            $price = lookup($_POST["symbol"])["price"];
            // get number of shares
            $shares = query("SELECT * FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"])[0]["shares"];
            // remove stock from portfolio
            query("DELETE FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            // update user's cash
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $price * $shares, $_SESSION["id"]);
            
            // add history
            query("INSERT INTO history (id, action, symbol, shares, price) VALUES(?, 'SELL', ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $shares, $price);
            
            redirect("/");
        }
    }
    else
    {
        // render sell form
        render("sell_form.php", ["title" => "Sell form"]);
    }

?>
