<div>
    <table class="table table-hover table-bordered">
        <caption>History</caption>
        <thead>
            <tr>
                <td>Transaction</td>
                <td>Date/Time</td>
                <td>Symbol</td>
                <td>Shares</td>
                <td>Price</td>
            </tr>
        <thead>
        <tbody>
        <?php foreach ($history as $history): ?>
            <tr>
                <td><?= $history["transaction"] ?></td>
                <td><?= $history["dateTime"] ?></td>
                <td><?= $history["symbol"] ?></td>
                <td><?= $history["shares"] ?></td>
                <td><?= $history["price"] ?></td>
            </tr>
        <? endforeach ?>
        </tbody>
    </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
