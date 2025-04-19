"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;
var _reactNative = require("react-native");
var _package = _interopRequireDefault(require("../package.json"));
function _interopRequireDefault(e) { return e && e.__esModule ? e : { default: e }; }
const LINKING_ERROR = `
The package '${_package.default.name}' doesn't seem to be linked. Make sure:
${_reactNative.Platform.select({
  ios: `- You have run 'pod install'`,
  default: ''
})} 
- You rebuilt the app after installing the package
- You are not using Expo Go
`.trim();

// @ts-expect-error
const isTurboModuleEnabled = global.__turboModuleProxy != null;
const OcrModule = isTurboModuleEnabled ? require('./NativeOcr').default : _reactNative.NativeModules.RNOcr;
const Ocr = OcrModule ? OcrModule : new Proxy({}, {
  get() {
    throw new Error(LINKING_ERROR);
  }
});

// @ts-ignore
const jsiModule = global;
if (_reactNative.Platform.OS === 'android' && !jsiModule.create) {
  throw new Error(`${_package.default.name}: failed to load JSI module`);
}
const _module = _reactNative.Platform.OS === 'ios' ? Ocr : jsiModule;
var _default = exports.default = _module;
//# sourceMappingURL=OcrModule.js.map