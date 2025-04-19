"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.Ocr = void 0;
var _OcrModule = _interopRequireDefault(require("./OcrModule"));
function _interopRequireDefault(e) { return e && e.__esModule ? e : { default: e }; }
class Ocr {
  // default options is at shared.h
  static async create(options) {
    await _OcrModule.default.create(options);
    return new Ocr();
  }
  detect(rawImagePath) {
    const imagePath = rawImagePath.replace('file://', '');
    return _OcrModule.default.detect(imagePath);
  }
}
exports.Ocr = Ocr;
//# sourceMappingURL=Ocr.js.map