const expressSitemapXml = require("express-sitemap-xml");

const staticURLs = [
  "", // don't forget the base route! 
  "/2-3-tree",
  "/2-3-4-tree",
  "/binary-tree",
  "/avl-tree",
  "/b-tree",
  "/about",
  "/how-to",
];

async function getURLs() {
  return staticURLs;
}

module.exports = expressSitemapXml(getURLs, "http://www.treeviz.xyz/");