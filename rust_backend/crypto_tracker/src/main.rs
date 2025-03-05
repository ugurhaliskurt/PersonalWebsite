// src/main.rs
mod models;
mod fetch;

use actix_web::{web, App, HttpServer};
use fetch::get_price_data;
use actix_cors::Cors;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .wrap(Cors::default()) // Enable CORS
            .route("/price/{coin}/{days}", web::get().to(get_price_data)) // Define the route with parameters
    })
    .bind("127.0.0.1:8080")? // Bind the server to a specific address and port
    .run()
    .await
}