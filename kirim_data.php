<?php
    include 'koneksi.php';

    if($_SERVER["REQUEST_METHOD"] == "GET") {
        $distance = $_GET["data"];

        $query = "UPDATE tbl_sensor SET nilai_sensor='$distance'";
        $result = mysqli_query($koneksi, $query);
    }
?>