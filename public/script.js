document.addEventListener('DOMContentLoaded', () => {
    // Initialize Lucide icons
    lucide.createIcons();

    // Mobile menu toggle
    const menuToggle = document.getElementById('menu-toggle');
    const navMenu = document.querySelector('nav ul');

    menuToggle.addEventListener('click', () => {
        navMenu.classList.toggle('show');
    });

    // Smooth scrolling for navigation links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            document.querySelector(this.getAttribute('href')).scrollIntoView({
                behavior: 'smooth'
            });
        });
    });

    // Highlight active navigation item and change header background
    const header = document.getElementById('header');
    const sections = document.querySelectorAll('section');
    const navItems = document.querySelectorAll('nav ul li a');

    window.addEventListener('scroll', () => {
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
    });

    // Add parallax effect to profile photo
    const profileImage = document.getElementById('profile-image');
    window.addEventListener('scroll', () => {
        const scrollPosition = window.pageYOffset;
        profileImage.style.transform = `translateY(${scrollPosition * 0.3}px)`;
    });
});