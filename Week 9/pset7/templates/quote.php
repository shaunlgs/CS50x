<?php

    // if stock lookup fail
    if ($s === false)
    {
        print("Wrong stock symbol!");
    }
    // else display stock price
    else
    {
        print("Price: " . number_format($s["price"], 2));
    }
?>
