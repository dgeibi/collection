const { resolve } = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const pkg = require('./package.json');

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

module.exports = () => ({
  entry: resolve(__dirname, 'src/index.js'),
  output: {
    path: resolve(__dirname, publicPath),
    filename: 'bundle.js',
    publicPath: '/',
  },
  module: { rules },
  plugins: [
    new HtmlWebpackPlugin({
      title: pkg.name,
      template: 'templates/index.ejs',
    }),
  ],
  devServer: {
    contentBase: resolve(__dirname, publicPath),
  },
});
