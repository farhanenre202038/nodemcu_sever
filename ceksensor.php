<?php
    include 'koneksi.php';

    $sql = mysqli_query($koneksi, "SELECT * FROM tbl_sensor");
    $data = mysqli_fetch_array($sql);
    $nilai =  $data["nilai_sensor"];

    echo $nilai . " cm";
?>