document.addEventListener('DOMContentLoaded', () => {
    // Initialize Lucide icons
    lucide.createIcons();

    const header = document.getElementById('header');
    const mobileMenu = document.getElementById('mobile-menu');
    const sections = document.querySelectorAll('section');
    const navItems = document.querySelectorAll('nav ul li a');

    // Smooth scrolling for navigation links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const target = document.querySelector(this.getAttribute('href'));
            const headerOffset = 100;
            const elementPosition = target.getBoundingClientRect().top;
            const offsetPosition = elementPosition + window.pageYOffset - headerOffset;

            window.scrollTo({
                top: offsetPosition,
                behavior: 'smooth'
            });
        });
    });

    // Highlight active navigation item and change header background
    function updateActiveSection() {
        let current = '';
        sections.forEach(section => {
            const sectionTop = section.offsetTop;
            const sectionHeight = section.clientHeight;
            if (pageYOffset >= sectionTop - sectionHeight / 3) {
                current = section.getAttribute('id');
            }
        });

        navItems.forEach(item => {
            item.classList.remove('active');
            if (item.getAttribute('href').slice(1) === current) {
                item.classList.add('active');
            }
        });

        // Change header background on scroll
        if (window.scrollY > 50) {
            header.style.backgroundColor = 'rgba(30, 58, 138, 1)';
        } else {
            header.style.backgroundColor = 'rgba(30, 58, 138, 0.8)';
        }
    }

    window.addEventListener('scroll', updateActiveSection);
    window.addEventListener('load', updateActiveSection);

    // Add parallax effect to profile photo
    const profileImage = document.getElementById('profile-image');
    window.addEventListener('scroll', () => {
        const scrollPosition = window.pageYOffset;
        profileImage.style.transform = `translateY(${scrollPosition * 0.3}px)`;
    });
});

// Mobile menu toggle function
function toggleMobileMenu() {
    const mobileMenu = document.getElementById('mobile-menu');
    mobileMenu.classList.toggle('show');
    document.body.classList.toggle('menu-open');
}

// Close mobile menu function
function closeMobileMenu() {
    const mobileMenu = document.getElementById('mobile-menu');
    mobileMenu.classList.remove('show');
    document.body.classList.remove('menu-open');
}