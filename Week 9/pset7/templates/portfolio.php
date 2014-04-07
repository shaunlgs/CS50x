<nav class="navbar navbar-default" role="navigation">
    <div class="collapse navbar-collapse">
      <ul class="nav navbar-nav">
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="history.php">History</a></li>
      </ul>
      <ul class="nav navbar-nav navbar-right">
        <li><a href="password.php">Change password</a></li>
      </ul>
    </div>
</nav>

<div>
    Your cash balance: <span class="badge">$<?= $cash ?></span>
    <br>
    <br>
</div>

<div>
    <table class="table table-hover table-bordered">
        <caption>Stocks</caption>
        <thead>
            <tr>
                <td>Name</td>
                <td>Symbol</td>
                <td>Price</td>
                <td>Shares</td>
            </tr>
        <thead>
        <tbody>
        <?php foreach ($positions as $positions): ?>
            <tr>
                <td><?= $positions["name"] ?></td>
                <td><?= $positions["symbol"] ?></td>
                <td><?= $positions["price"] ?></td>
                <td><?= $positions["shares"] ?></td>
            </tr>
        <? endforeach ?>
        </tbody>
    </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
