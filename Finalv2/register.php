<?php 
    require("config.php");
    if(!empty($_POST)) 
    { 
        if(empty($_POST['username'])) 
        { die("Por favor introduza um nome de utilizador."); } 
        if(empty($_POST['password'])) 
        { die("Por favor introduza uma palavra passe."); } 
        if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)) 
        { die("Endreço de E-mail nao valido."); } 
         
        $query = " 
            SELECT 
                1 
            FROM users 
            WHERE 
                username = :username 
        "; 
        $query_params = array( ':username' => $_POST['username'] ); 
        try { 
            $stmt = $db->prepare($query); 
            $result = $stmt->execute($query_params); 
        } 
        catch(PDOException $ex){ die("Failed to run query: " . $ex->getMessage()); } 
        $row = $stmt->fetch(); 
        if($row){ die("Este nome de utilizador ja esta em uso."); } 
        $query = " 
            SELECT 
                1 
            FROM users 
            WHERE 
                email = :email 
        "; 
        $query_params = array( 
            ':email' => $_POST['email'] 
        ); 
        try { 
            $stmt = $db->prepare($query); 
            $result = $stmt->execute($query_params); 
        } 
        catch(PDOException $ex){ die("Failed to run query: " . $ex->getMessage());} 
        $row = $stmt->fetch(); 
        if($row){ die("Este email ja esta em uso."); } 
        
        $query = " 
            INSERT INTO users ( 
                username, 
                password, 
                salt, 
                email 
            ) VALUES ( 
                :username, 
                :password, 
                :salt, 
                :email 
            ) 
        "; 
         
        $salt = dechex(mt_rand(0, 2147483647)) . dechex(mt_rand(0, 2147483647)); 
        $password = hash('sha256', $_POST['password'] . $salt); 
        for($round = 0; $round < 65536; $round++){ $password = hash('sha256', $password . $salt); } 
        $query_params = array( 
            ':username' => $_POST['username'], 
            ':password' => $password, 
            ':salt' => $salt, 
            ':email' => $_POST['email'] 
        ); 
        try {  
            $stmt = $db->prepare($query); 
            $result = $stmt->execute($query_params); 
        } 
        catch(PDOException $ex){ die("Failed to run query: " . $ex->getMessage()); } 
        header("Location: index.php"); 
        die("Redirecting to index.php"); 
    } 
?>
<!DOCTYPE html>
<html>
  <head>
    <title>BlackBird </title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/skeleton.css">
    <link rel="stylesheet" href="css/normalize.css">
    <link rel="stylesheet" href="css/men.css">
    <link rel="stylesheet" href="css/style.css">
    <link rel="stylesheet" href="css/login.css">
    <script src="js/jquery-2.1.3.min.js"></script>
    <script src="js/functions.js"></script>
  </head>
  <body>
    <nav>
      <ul>
        <li><a href="Index.php">Login</a></li>
        <li><a href="register.php">Registo</a></li>
        <li><a href="Secret.php">Area Cliente</a></li>
        <li><a href="about.html">Sobre Nos</a></li>
        <li><a href="women.html">Mulher</a></li>
        <li><a href="men.html">Homem</a></li>
        <li><a href="index.html">Home</a></li>
      </ul>
    </nav>
    <header class="background">
      <div class="logo"></div>
    </header>
    <article>
      <hr>
      <h1>Registo</h1>
      <hr>
        <form action="register.php" method="post"> 
        <label>Username:</label> 
        <input type="text" name="username" value="" /> 
        <label>Email: <strong style="color:darkred;">*</strong></label> 
        <input type="text" name="email" value="" /> 
        <label>Password:</label> 
        <input type="password" name="password" value="" /> <br /><br />
        <p style="color:darkred;"></p><br />
        <input type="submit" class="btn btn-info" value="Registo" /> 
        </form>
    </article>
    <footer>
      <div class="row footer">
        <div class="columns three"><strong>ENCONTRA-NOS:</strong>
          <ul>
            <li><a href="">Twitter</a></li>
            <li><a href="">Facebook</a></li>
            <li><a href="">Pinterest</a></li>
          </ul>
        </div>
        <div class="columns three"><strong>FEITO POR</strong>
          <ul>
            <li>Miguel Dias</li>
            <li>Gabriel Silva</li>
          </ul>
        </div>
      </div>
    </footer>
  </html>
    
    