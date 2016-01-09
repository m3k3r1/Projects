<?php 
    require("config.php"); 
    $submitted_username = ''; 
    if(!empty($_POST)){ 
        $query = " 
            SELECT 
                id, 
                username, 
                password, 
                salt, 
                email 
            FROM users 
            WHERE 
                username = :username 
        "; 
        $query_params = array( 
            ':username' => $_POST['username'] 
        ); 
         
        try{ 
            $stmt = $db->prepare($query); 
            $result = $stmt->execute($query_params); 
        } 
        catch(PDOException $ex){ die("Failed to run query: " . $ex->getMessage()); } 
        $login_ok = false; 
        $row = $stmt->fetch(); 
        if($row){ 
            $check_password = hash('sha256', $_POST['password'] . $row['salt']); 
            for($round = 0; $round < 65536; $round++){
                $check_password = hash('sha256', $check_password . $row['salt']);
            } 
            if($check_password === $row['password']){
                $login_ok = true;
            } 
        } 

        if($login_ok){ 
            unset($row['salt']); 
            unset($row['password']); 
            $_SESSION['user'] = $row;  
            header("Location: Secret.php"); 
            die("Redirecting to: Secret.php"); 
        } 
        else{ 
            print("Login Failed."); 
            $submitted_username = htmlentities($_POST['username'], ENT_QUOTES, 'UTF-8'); 
        } 
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
        <li><a href="Register.php">Registo</a></li>
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
      <h1>Log In</h1>
      <hr>
    <form action="index.php" method="post"> 
                    Username:<br /> 
                    <input type="text" name="username" value="<?php echo $submitted_username; ?>" /> 
                    <br /><br /> 
                    Password:<br /> 
                    <input type="password" name="password" value="" /> 
                    <br /><br /> 
                    <input type="submit" class="btn btn-info" value="Login" /> 
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
