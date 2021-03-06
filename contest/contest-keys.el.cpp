(defun kactl-compile () (interactive)
  (shell-command (concat "g++ -ansi -lm -Wall -o "
			 (file-name-sans-extension buffer-file-name)
			 " " buffer-file-name)))

(defun kactl-new-file (N) (interactive "FCFF: ") 
  (find-file N) (or (file-exists-p N)
		    (not (string-equal (file-name-extension N) "cc"))
		    (insert-file "Template.cc")))

(defun kactl-test () (interactive) 
  (let ((N (file-name-sans-extension buffer-file-name)))
    (shell-command (concat N " < " N ".in &"))))
;; This line replaces the above two lines on input
;; from file instead of stdin
;;(shell-command (file-name-sans-extension buffer-file-name)))

(defun kactl-send () (interactive)
  (and (string-equal (file-name-extension buffer-file-name) "cc")
       (y-or-n-p "Send? ") (shell-command 
			    (concat "submit " buffer-file-name))))

(global-set-key "\C-x\C-f" 'kactl-new-file)
(global-set-key "\C-cc" 'kactl-compile)
(global-set-key "\C-ct" 'kactl-test)
(global-set-key "\C-cs" 'kactl-send)
