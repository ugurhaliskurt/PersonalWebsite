// src/models.rs
use serde::{Deserialize, Serialize};

#[derive(Debug, Deserialize, Serialize)] // Add Serialize here
pub struct MarketChart {
    pub prices: Vec<(f64, f64)>, // (timestamp, price)
}
