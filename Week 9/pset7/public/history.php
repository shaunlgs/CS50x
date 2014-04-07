<?php
    // configuration
    require("../includes/config.php");
    
    // store an array of associative arrays in $history
    $history = [];
    $row = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    foreach ($row as $row)
    {
            $history[] = [
            "transaction" => $row["action"],
            "dateTime" => $row["dateTime"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"],
            ];
    }

    // render portfolio
    render("history.php", ["history" => $history, "title" => "History"]);
?>
