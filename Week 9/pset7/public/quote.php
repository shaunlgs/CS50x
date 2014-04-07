<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup stock price
        $s = lookup($_POST["symbol"]);
        // redirect to portfolio
        render("quote.php", ["title" => "Quote price", "s" => $s]);
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
