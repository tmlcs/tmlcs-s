function MainPage() {
    const content = `
	<section>
      	   <div class="welcome">
	      <div class="welcome-card">
	           <div class="title-welcome">
                  <h2>Bienvenido a TMLCS CollectionS (Servidor en Mantenimiento)</h2>
              </div>
              <img src="/favicon.png">
              <div class="main-welcome">
                   <p>El servidor está actualmente en mantenimiento. Estamos trabajando para mejorar tu experiencia.</p>
                   <p>Estimamos que el servicio estará disponible nuevamente en aproximadamente 10 hora.</p>
                   <p>Mientras tanto, disculpa las molestias y gracias por tu paciencia.</p>
              </div>
              <div class="tendencias">
		   <div class="tendencias-card">
		        <p>TENDECIAS</p>
                        <p>EXCLUSIVAS</p>
                        <a href="#"></a>
		   </div>
              </div>
              <div class="watchwelcome">
                   <a href="#whitepaper" class="btn">Ver el Whitepaper</a>
                   <a href="#productos" class="btn">Ver todos los Productos</a>
              </div>
	      </div>
           </div>
        </section>

	<article class="index-banner">
      	<h2>Ofertas Destacadas</h2>
      	<div class="underline-banner"></div>
      	<div class="scroll-banner">
           <div class="icon-slider">
               <img src="">
               <p>Complementos (anillos)</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/favicon.png">
               <p>Sombreros</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Gorras</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Gafas</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Chubasqueros</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Chaqueta</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Camiseta</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Camisa</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Ropa Interior</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Pantalones</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Calcetines</p>
           </div>
           <div class="icon-slider">
               <img src="../IMG/adidas.png">
               <p>Zapatillas</p>
           </div>
        </div>
        </article>

	<article class="index-banner">
      <h2>Productos en Tendencia</h2>
      <div class="underline-banner"></div>
      <div class="scroll-banner">
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Complementos (anillos)</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Sombreros</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Gorras</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Gafas</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Chubasqueros</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Chaqueta</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Camiseta</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Camisa</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Ropa Interior</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Pantalones</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Calcetines</p>
        </div>
        <div class="icon-slider">
          <img src="../IMG/adidas.png">
          <p>Zapatillas</p>
        </div>
      </div>
    </article>

	<article class="index-banner">
      	<h2>Productos de Temporada</h2>
      	<div class="underline-banner"></div>
      	<div class="scroll-banner">
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
        </div>
    	</article>

	<article class="index-banner">
      	<h2>Todas las Colleciones</h2>
      	<div class="underline-banner"></div>
      	<div class="scroll-banner">
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
      	</div>
    	</article>

	<article class="index-banner">
        <h2>Todas las Categorias</h2>
        <div class="underline-banner"></div>
        <div class="scroll-banner">
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
        </div>
        </article>

	<article class="index-banner">
        <h2>Todas las Marcas</h2>
        <div class="underline-banner"></div>
        <div class="scroll-banner">
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
           <div class="icon-slider"></div>
        </div>
        </article>

	`;
    document.getElementById('Main-Content').innerHTML = content;
};

window.onload = MainPage;




//Dark-mode

document.addEventListener('DOMContentLoaded', () => {
            const darkModeToggle = document.getElementById('darkmode-toggle');
            const body = document.body;

            // Verificar el estado del modo oscuro al cargar la página
            const darkMode = localStorage.getItem('dark-mode');
            if (darkMode === 'enabled') {
                body.classList.add('dark-mode');
                darkModeToggle.checked = true;
            } else {
                body.classList.remove('dark-mode');
                darkModeToggle.checked = false;
            }

            // Escuchar cambios en el toggle
            darkModeToggle.addEventListener('change', () => {
                if (darkModeToggle.checked) {
                    enableDarkMode();
                } else {
                    disableDarkMode();
                }
            });

            // Función para habilitar el modo oscuro
            function enableDarkMode() {
                body.classList.add('dark-mode');
                darkModeToggle.checked = true;
                localStorage.setItem('dark-mode', 'enabled');
            }

            // Función para deshabilitar el modo oscuro
            function disableDarkMode() {
                body.classList.remove('dark-mode');
                darkModeToggle.checked = false;
                localStorage.setItem('dark-mode', 'disabled');
            }
        });

// Función para generar un color RGB aleatorio
function getRandomColor() {
  let r = Math.floor(Math.random() * 256);
  let g = Math.floor(Math.random() * 256);
  let b = Math.floor(Math.random() * 256);
  return "rgb(" + r + ", " + g + ", " + b + ")";
}

// Actualizar el color del borde cada cierto intervalo de tiempo
setInterval(function() {
  let welcome = document.querySelector('.elcome');
  welcome.style.borderColor = getRandomColor();
}, 1000); // Cambiar el color cada segundo (1000 milisegundos)
