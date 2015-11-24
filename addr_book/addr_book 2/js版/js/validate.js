$(document).ready(function($) {
    var Toast = {
        isInited: false,
        elem: null,
        timeout: null,
        timelong: 2000,
        id: "toast",
        showCln: "on",

        isLoading: false,

        _clearTimeout: function() {
            clearTimeout(this.timeout);
            this.timeout = null;
        },

        _setTimeout: function(callback) {
            this._clearTimeout();
            this.timeout = setTimeout($.proxy(callback, this), this.timelong);
        },

        show: function(text) {
            if (!this.isInited) return;
            this.elem.html('<p>' + text + '</p>').addClass(this.showCln);
            this.isLoading = false;
            this._setTimeout(this.hide);
        },

        hide: function() {
            if (!this.isInited) return;
            this.elem.removeClass(this.showCln);
            this._clearTimeout();
        },


        init: function() {
            
            var toast_screen = document.getElementsByClassName("toast-screen");
            var toast = document.createElement("div");
            toast.setAttribute("id", this.id);
            toast.setAttribute("class", this.id);
            toast_screen[0].appendChild(toast);
            
            this.elem = $('#' + this.id);
            this.isInited = true;

        }

    };

    Toast.init();

    //登陆页面的验证

    function usernameIsValid(username) {
        return /^[0-9a-zA-Z_.-]{6,12}$/.test(username);
    }

    function passwordIsValid(password) {
        return /^(?=.*?[a-zA-Z])(?=.*?\d).{6,}$/.test(password);
    }


    var failset = [false, false, false, false]
        // 用户名未填，用户名不符合要求，密码未填，密码不符合要求

    var toastset = ["请输入用户名:D",
                    "用户名需大于5个字符，小于13个字符",
                    "请输入密码XD",
                    "密码需要大于5个字符，必须包含数字与字母"]


    var login_toast = document.getElementById("login-toast");
    
    if (login_toast) {
        login_toast.addEventListener('click', function() {

            var username = document.getElementById("login-name").value;
            var password = document.getElementById("login-pass").value;

            if (username == "") {
                failset[0] = true;
            }

            if (usernameIsValid(username) == false) {
                failset[1] = true;
            }

            if (password == "") {
                failset[2] = true;
            }

            if (passwordIsValid(password) == false) {
                failset[3] = true;
            }

            for (var i = 0; i < failset.length; i++) {
                if (failset[i] == true) {
                    Toast.show(toastset[i]);
                    break;
                };
            };

            failset = [false, false, false, false];
        });

        
    };
    
    //新建联系人页面的验证

    var add_toast = document.getElementById("add-toast");

    if (add_toast) {
        add_toast.addEventListener('click', function() {
            var name = $('#new-name').val();
            if (name == "") {
                Toast.show("请输入联系人姓名 :D");
            }

        });
    };



});
