const { resolve } = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const pkg = require('./package.json');
const Config = require('wtf-webpack-config');
const uglifyjs = require('wtf-webpack-config/plugins/uglifyjs');
const define = require('wtf-webpack-config/plugins/define');

const publicPath = 'public';
const rules = [
  {
    test: /\.js$/,
    use: [
      { loader: 'babel-loader' },
    ],
    include: [
      resolve(__dirname, 'src'),
    ],
  },
];
module.exports = (env = {}) => {
  const isProduction = env.production === true;

  return new Config({
    entry: [
      resolve(__dirname, 'src/index.js'),
    ],
    output: {
      path: resolve(__dirname, publicPath),
      filename: 'bundle.js',
      publicPath: '/ ',
    },
    module: { rules },
    plugins: [
      new HtmlWebpackPlugin({
        title: pkg.name,
        template: 'templates/index.ejs',
      }),
    ],
    devServer: {
      hot: true,
      contentBase: resolve(__dirname, publicPath),
    },
  }).use(uglifyjs(), isProduction)
    .use(define(), isProduction)
    .use((config) => {
      config.plugin(webpack.HotModuleReplacementPlugin);
    }, !isProduction)
    .toConfig();
};
