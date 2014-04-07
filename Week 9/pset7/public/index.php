<?php
    // configuration
    require("../includes/config.php");
    
    // store an array of associative arrays (each containing name of stock, current price of stock, shares the user have, and symbol of stock) in $position
    $positions = [];
    $cash = number_format(query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"], 2);
    $row = query("SELECT symbol, shares FROM portfolios WHERE id = ?", $_SESSION["id"]);
    foreach ($row as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);
?>
