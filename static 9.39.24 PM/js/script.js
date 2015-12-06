function Toast() {
    this.isInited=false;
    this.elem=null;
    this.timeout=null;
    this.timelong=2000;
    this.id="toast";
    this.showCln="on";

    this.isLoading= false;

    this._clearTimeout = function() {
        clearTimeout(this.timeout);
        this.timeout = null;
    };

    this._setTimeout = function(callback) {
        this._clearTimeout();
        this.timeout = setTimeout($.proxy(callback, this), this.timelong);
    };

    this.show = function(text) {
        if (!this.isInited) return;
        var strok = '';
        this.elem.html('<p>' + strok + text + '</p>').addClass(this.showCln);
        this.isLoading = false;
        this._setTimeout(this.hide);
    };

    this.hide = function() {
        if (!this.isInited) return;
        this.elem.removeClass(this.showCln);
        this._clearTimeout();
    };


    this.init = function() {
        $('.form-screen').append('<div id="' + this.id + '" class="' + this.id + '"></div>');
        this.elem = $('#' + this.id);
        this.isInited = true;

    };

}
