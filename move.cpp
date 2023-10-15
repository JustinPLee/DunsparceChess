#include "move.hpp"

Move::Move() {

};

Move::Move(uint32_t from, uint32_t to) {
    setFrom(from);
    setTo(to);
};

Move::Move(uint32_t from, uint32_t to, uint32_t flags) {
    setFrom(from);
    setTo(to);
    // set flags
    move |= (flags << 12);
};

void Move::clear() {
    move = 0;
};

uint32_t Move::getFrom() {
    // 0-5
    return move & 0x3f;
};

uint32_t Move::getTo() {
    // 6-11
    return (move >> 6) & 0x3f;
};

uint32_t Move::getCapture() {
    // 16-19
    return (move >> 16) & 0xf;
};

uint32_t Move::getPiece() {
    // 12-15
    return (move >> 12) & 0xf;
};

uint32_t Move::getPromotion() {
    // 20-23
    return (move >> 20) & 0xf;
};

uint32_t Move::setTo(uint32_t to) {
    // 6-11
    move &= 0xfffff03f;
    move |= (to & 0x3f) << 6;
};

uint32_t Move::setFrom(uint32_t from) {
    // 0-5
    move &= 0xffffffc0;
    move |= (from & 0x3f);
};

uint32_t Move::setCapture(uint32_t capture) {
    // 16-19
    move &= 0xfff0ffff;
    move |= (capture & 0xf) << 16;
};

uint32_t Move::setPiece(uint32_t piece) {
    // 12-15
    move &= 0xffff0fff;
    move |= (piece & 0xf) << 12;
};

uint32_t Move::setPromotion(uint32_t promotion) {
    // 20-23
    move &= 0xff0fffff;
    move |= (promotion & 0xf) << 20;
};

bool Move::isWhiteMove() {
    // 24
    
};

bool Move::isBlackMove() {
    
};

bool Move::isCapture() {

};

bool Move::isKingcaptured() {

};

bool Move::isRookMove() {

};

bool Move::isRookCaptured() {

};

bool Move::isKingMove() {

};

bool Move::isPawnMove() {

};

bool Move::isPawnDoubleMove() {

};

bool Move::isCroissant() {

};

bool Move::isPromotion() {

};

bool Move::isCastle() {

};

bool Move::isCastleShort() {

};

bool Move::isCastleLong() {

};