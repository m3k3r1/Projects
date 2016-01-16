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
    <script>
        funcion auth(form) {
          var user = from.user.value;
          alert ("You typed: " + TestVar);
        }
    </script>
  </head>
  <body>
    <nav>
      <ul>
        <li><a href="index.php">Login</a></li>
        <li><a href="register.php">Registo</a></li>
        <li><a href="secret.php">Area Cliente</a></li>
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
    <form NAME= "validation" ACTION="" METHOD="POST">
                    Username:<br />
                    <input  class="user" type="text" name="username"/>
                    <br /><br />
                    Password:<br />
                    <input class="pass" type="password" name="password"/>
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
