// src/main.rs
mod models;
mod fetch;

use actix_web::{web, App, HttpServer};
use fetch::get_price_data;
use actix_cors::Cors;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    println!("🚀 Server is starting...");
    HttpServer::new(|| {
        App::new()
            .wrap(Cors::default()) // Enable CORS
            .route("/price", web::get().to(get_price_data))
    })
    .bind("0.0.0.0:9081")? // Bind the server to a specific address and port
    .run()
    .await
}