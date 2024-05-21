use reqwest;
use scraper::{Html, Selector};
use std::error::Error;

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    
    let url = "https://tldr.tech/tech/2024-05-21";

    let response = reqwest::get(url).await?.text().await?;
    let document = Html::parse_document(&response);
    let selector = Selector::parse("div.mt-3").unwrap();


    for element in document.select(&selector) {
        let text = element.text().collect::<Vec<_>>().concat();
        println!("{}\n", text);
    }


    Ok(())
}
