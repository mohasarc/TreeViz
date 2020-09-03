const expressSitemapXml = require("express-sitemap-xml");

const staticURLs = [
  "", // don't forget the base route! 
  "/fullTreeView",
  "/about",
  "/how-to",
];

async function getURLs() {
  return staticURLs;
}

module.exports = expressSitemapXml(getURLs, "http://www.treeviz.xyz/");