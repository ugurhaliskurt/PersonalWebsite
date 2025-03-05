// src/fetch.rs
use reqwest;
use crate::models::MarketChart; // Import the MarketChart struct from models.rs
use actix_web::{web, Responder, HttpResponse};
use serde::Serialize;

#[derive(Serialize)]
pub struct ErrorResponse {
    pub error: String,
}

async fn fetch_crypto_price(url: &str) -> Result<MarketChart, reqwest::Error> {
    let response = reqwest::get(url).await?.json::<MarketChart>().await?;
    Ok(response)
}

pub async fn get_price_data(
    coin: web::Path<String>, 
    days: web::Path<i32>
) -> impl Responder {
    let url = format!(
        "https://api.coingecko.com/api/v3/coins/{}/market_chart?vs_currency=usd&days={}",
        coin, days
    );

    match fetch_crypto_price(&url).await {
        Ok(data) => HttpResponse::Ok().json(data), // Return JSON data
        Err(err) => {
            let error_response = ErrorResponse {
                error: format!("Error fetching price data: {}", err),
            };
            HttpResponse::InternalServerError().json(error_response)
        }
    }
}
