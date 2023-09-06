let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <expr> <Plug>(neosnippet_start_unite_snippet) unite#sources#neosnippet#start_complete()
inoremap <silent> <expr> <Plug>(neosnippet_jump) neosnippet#mappings#jump_impl()
inoremap <silent> <expr> <Plug>(neosnippet_expand) neosnippet#mappings#expand_impl()
inoremap <silent> <expr> <Plug>(neosnippet_jump_or_expand) neosnippet#mappings#jump_or_expand_impl()
inoremap <silent> <expr> <Plug>(neosnippet_expand_or_jump) neosnippet#mappings#expand_or_jump_impl()
snoremap  a<BS>
nnoremap  :noh
snoremap  a<BS>
nmap d :cs find d =expand("<cword>")	
nmap i :cs find i ^=expand("<cfile>")$
nmap f :cs find f =expand("<cfile>")	
nmap e :cs find e =expand("<cword>")	
nmap t :cs find t =expand("<cword>")	
nmap c :cs find c =expand("<cword>")	
nmap g :cs find g =expand("<cword>")	
nmap s :cs find s =expand("<cword>")	
nmap a :cs find a =expand("<cword>")
nmap d :cs find d =expand("<cword>")
nmap i :cs find i ^=expand("<cfile>")$
nmap f :cs find f =expand("<cfile>")
nmap e :cs find e =expand("<cword>")
nmap t :cs find t =expand("<cword>")
nmap c :cs find c =expand("<cword>")
nmap g :cs find g =expand("<cword>")
nmap s :cs find s =expand("<cword>")
nnoremap <silent> <expr> H context#util#map_H()
xmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <expr> zt context#util#map_zt()
snoremap <C-H> a<BS>
snoremap <Del> a<BS>
snoremap <BS> a<BS>
xnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
xnoremap <silent> <Plug>(neosnippet_register_oneshot_snippet) :call neosnippet#mappings#_register_oneshot_snippet()
xnoremap <silent> <Plug>(neosnippet_expand_target) :call neosnippet#mappings#_expand_target()
xnoremap <silent> <Plug>(neosnippet_get_selected_text) :call neosnippet#helpers#get_selected_text(visualmode(), 1)
xmap <Plug>(neosnippet_jump) <Plug>(neosnippet_jump)
xmap <Plug>(neosnippet_expand) <Plug>(neosnippet_expand)
xmap <Plug>(neosnippet_jump_or_expand) <Plug>(neosnippet_jump_or_expand)
xmap <Plug>(neosnippet_expand_or_jump) <Plug>(neosnippet_expand_or_jump)
nmap <Plug>(neosnippet_jump) g<Plug>(neosnippet_jump)
nmap <Plug>(neosnippet_expand) g<Plug>(neosnippet_expand)
nmap <Plug>(neosnippet_jump_or_expand) g<Plug>(neosnippet_jump_or_expand)
nmap <Plug>(neosnippet_expand_or_jump) g<Plug>(neosnippet_expand_or_jump)
snoremap <silent> <expr> <Plug>(neosnippet_jump) neosnippet#mappings#jump_impl()
snoremap <silent> <expr> <Plug>(neosnippet_expand) neosnippet#mappings#expand_impl()
snoremap <silent> <expr> <Plug>(neosnippet_jump_or_expand) neosnippet#mappings#jump_or_expand_impl()
snoremap <silent> <expr> <Plug>(neosnippet_expand_or_jump) neosnippet#mappings#expand_or_jump_impl()
nmap <C-@><C-@>d :vert scs find d =expand("<cword>")
nmap <Nul><Nul>d :vert scs find d =expand("<cword>")
nmap <C-@><C-@>i :vert scs find i ^=expand("<cfile>")$	
nmap <Nul><Nul>i :vert scs find i ^=expand("<cfile>")$	
nmap <C-@><C-@>f :vert scs find f =expand("<cfile>")	
nmap <Nul><Nul>f :vert scs find f =expand("<cfile>")	
nmap <C-@><C-@>e :vert scs find e =expand("<cword>")
nmap <Nul><Nul>e :vert scs find e =expand("<cword>")
nmap <C-@><C-@>t :vert scs find t =expand("<cword>")
nmap <Nul><Nul>t :vert scs find t =expand("<cword>")
nmap <C-@><C-@>c :vert scs find c =expand("<cword>")
nmap <Nul><Nul>c :vert scs find c =expand("<cword>")
nmap <C-@><C-@>g :vert scs find g =expand("<cword>")
nmap <Nul><Nul>g :vert scs find g =expand("<cword>")
nmap <C-@><C-@>s :vert scs find s =expand("<cword>")
nmap <Nul><Nul>s :vert scs find s =expand("<cword>")
nmap <C-@>d :scs find d =expand("<cword>")	
nmap <Nul>d :scs find d =expand("<cword>")	
nmap <C-@>i :scs find i ^=expand("<cfile>")$	
nmap <Nul>i :scs find i ^=expand("<cfile>")$	
nmap <C-@>f :scs find f =expand("<cfile>")	
nmap <Nul>f :scs find f =expand("<cfile>")	
nmap <C-@>e :scs find e =expand("<cword>")	
nmap <Nul>e :scs find e =expand("<cword>")	
nmap <C-@>t :scs find t =expand("<cword>")	
nmap <Nul>t :scs find t =expand("<cword>")	
nmap <C-@>c :scs find c =expand("<cword>")	
nmap <Nul>c :scs find c =expand("<cword>")	
nmap <C-@>g :scs find g =expand("<cword>")	
nmap <Nul>g :scs find g =expand("<cword>")	
nmap <C-@>s :scs find s =expand("<cword>")	
nmap <Nul>s :scs find s =expand("<cword>")	
nmap <C-Bslash>d :cs find d =expand("<cword>")	
nmap <C-Bslash>i :cs find i ^=expand("<cfile>")$
nmap <C-Bslash>f :cs find f =expand("<cfile>")	
nmap <C-Bslash>e :cs find e =expand("<cword>")	
nmap <C-Bslash>t :cs find t =expand("<cword>")	
nmap <C-Bslash>c :cs find c =expand("<cword>")	
nmap <C-Bslash>g :cs find g =expand("<cword>")	
nmap <C-Bslash>s :cs find s =expand("<cword>")	
nnoremap <S-CR> O
nmap <C-Space><C-Space>a:vert scs find a =expand("<cword>")
nmap <C-Space><C-Space>d:vert scs find d =expand("<cword>")
nmap <C-Space><C-Space>i:vert scs find i ^=expand("<cfile>")$
nmap <C-Space><C-Space>e:vert scs find e =expand("<cword>")
nmap <C-Space><C-Space>t:vert scs find t =expand("<cword>")
nmap <C-Space><C-Space>c:vert scs find c =expand("<cword>")
nmap <C-Space><C-Space>g:vert scs find g =expand("<cword>")
nmap <C-Space><C-Space>s:vert scs find s =expand("<cword>")
nmap <C-Space>a :scs find a =expand("<cword>")
nmap <C-Space>d :scs find d =expand("<cword>")
nmap <C-Space>i :scs find i ^=expand("<cfile>")$
nmap <C-Space>f :scs find f =expand("<cfile>")
nmap <C-Space>e :scs find e =expand("<cword>")
nmap <C-Space>t :scs find t =expand("<cword>")
nmap <C-Space>c :scs find c =expand("<cword>")
nmap <C-Space>g :scs find g =expand("<cword>")
nmap <C-Space>s :scs find s =expand("<cword>")
nmap <C-_>a :cs find a =expand("<cword>")
nmap <C-_>d :cs find d =expand("<cword>")
nmap <C-_>i :cs find i ^=expand("<cfile>")$
nmap <C-_>f :cs find f =expand("<cfile>")
nmap <C-_>e :cs find e =expand("<cword>")
nmap <C-_>t :cs find t =expand("<cword>")
nmap <C-_>c :cs find c =expand("<cword>")
nmap <C-_>g :cs find g =expand("<cword>")
nmap <C-_>s :cs find s =expand("<cword>")
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=indent,eol,start
set cscopetag
set cscopeverbose
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hlsearch
set printoptions=paper:letter
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/etc/vim,/usr/share/vim/vimfiles,~/.cache/dein/repos/github.com/Shougo/dein.vim,~/.cache/dein/.cache/.vimrc/.dein,/usr/share/vim/vim90,~/.cache/dein/.cache/.vimrc/.dein/after,/usr/share/vim/vimfiles/after,/etc/vim/after,/var/lib/vim/addons/after,~/.vim/after,~/.cache/dein/repos/github.com/Shougo/dein.vim
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/inner_unikernels/linux/kernel/bpf
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +7186 verifier.c
badd +91 ~/inner_unikernels/linux/include/linux/bpf.h
badd +163 ~/inner_unikernels/linux/kernel/bpf/offload.c
badd +5553 ~/inner_unikernels/linux/include/uapi/linux/bpf.h
badd +97 ~/.vimrc
badd +57 ~/inner_unikernels/linux/include/uapi/linux/bpf_common.h
badd +5733 ~/inner_unikernels/linux/usr/include/linux/bpf.h
argglobal
%argdel
$argadd verifier.c
edit verifier.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 49 + 50) / 101)
exe '2resize ' . ((&lines * 49 + 50) / 101)
argglobal
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinscopedecls=public,protected,private
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal cursorlineopt=both
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal fillchars=
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
set foldlevel=99
setlocal foldlevel=99
setlocal foldmarker={{{,}}}
set foldmethod=syntax
setlocal foldmethod=syntax
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal listchars=
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,octal,hex
setlocal nonumber
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=8
setlocal noshortname
setlocal showbreak=
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal nosmartindent
setlocal nosmoothscroll
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal thesaurusfunc=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal virtualedit=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
1159
normal! zo
2741
normal! zo
2792
normal! zo
2851
normal! zo
2852
normal! zo
3784
normal! zo
3796
normal! zo
5375
normal! zo
5414
normal! zo
5834
normal! zo
5921
normal! zo
6136
normal! zo
7173
normal! zo
7365
normal! zo
9833
normal! zo
9835
normal! zo
9860
normal! zo
10234
normal! zo
10353
normal! zo
10890
normal! zo
10936
normal! zo
11036
normal! zo
11073
normal! zo
11164
normal! zo
11195
normal! zo
11409
normal! zo
11432
normal! zo
11645
normal! zo
12068
normal! zo
12077
normal! zo
12160
normal! zo
12283
normal! zo
12310
normal! zo
12407
normal! zo
12440
normal! zo
12454
normal! zo
12492
normal! zo
12494
normal! zo
12507
normal! zo
12534
normal! zo
12551
normal! zo
12576
normal! zo
12602
normal! zo
12621
normal! zo
12634
normal! zo
12651
normal! zo
12670
normal! zo
12713
normal! zo
12722
normal! zo
12729
normal! zo
12778
normal! zo
12811
normal! zo
12844
normal! zo
12911
normal! zo
12932
normal! zo
12962
normal! zo
12976
normal! zo
12991
normal! zo
13019
normal! zo
13036
normal! zo
13049
normal! zo
13075
normal! zo
13124
normal! zo
13176
normal! zo
13206
normal! zo
13232
normal! zo
13256
normal! zo
13278
normal! zo
13291
normal! zo
13298
normal! zo
13377
normal! zo
13387
normal! zo
13412
normal! zo
13437
normal! zo
13457
normal! zo
13499
normal! zo
13526
normal! zo
13565
normal! zo
13576
normal! zo
13617
normal! zo
13685
normal! zo
13687
normal! zo
13714
normal! zo
13737
normal! zo
13797
normal! zo
13819
normal! zo
13826
normal! zo
13827
normal! zo
13849
normal! zo
13876
normal! zo
13890
normal! zo
13895
normal! zo
13935
normal! zo
13954
normal! zo
14022
normal! zo
14046
normal! zo
14097
normal! zo
14164
normal! zo
14172
normal! zo
14252
normal! zo
14302
normal! zo
14373
normal! zo
14399
normal! zo
14415
normal! zo
14486
normal! zo
14495
normal! zo
14531
normal! zo
14547
normal! zo
14561
normal! zo
14588
normal! zo
14592
normal! zo
14657
normal! zo
14664
normal! zo
14694
normal! zo
14697
normal! zo
14718
normal! zo
14757
normal! zo
14806
normal! zo
14836
normal! zo
14849
normal! zo
14865
normal! zo
14876
normal! zo
14902
normal! zo
14976
normal! zo
14991
normal! zo
14993
normal! zo
15048
normal! zo
15083
normal! zo
15129
normal! zo
15140
normal! zo
15178
normal! zo
15316
normal! zo
15331
normal! zo
15345
normal! zo
12407
normal! zo
12440
normal! zo
12454
normal! zo
12492
normal! zo
12494
normal! zo
12507
normal! zo
12534
normal! zo
12551
normal! zo
12576
normal! zo
12602
normal! zo
12621
normal! zo
12634
normal! zo
12651
normal! zo
12670
normal! zo
12713
normal! zo
12722
normal! zo
12729
normal! zo
12778
normal! zo
12811
normal! zo
12844
normal! zo
12911
normal! zo
12932
normal! zo
12962
normal! zo
12976
normal! zo
12991
normal! zo
13019
normal! zo
13036
normal! zo
13049
normal! zo
13075
normal! zo
13124
normal! zo
13176
normal! zo
13206
normal! zo
13232
normal! zo
13256
normal! zo
13278
normal! zo
13291
normal! zo
13298
normal! zo
13377
normal! zo
13387
normal! zo
13412
normal! zo
13437
normal! zo
13457
normal! zo
13499
normal! zo
13526
normal! zo
13565
normal! zo
13576
normal! zo
13617
normal! zo
13685
normal! zo
13687
normal! zo
13714
normal! zo
13737
normal! zo
13797
normal! zo
13819
normal! zo
13826
normal! zo
13827
normal! zo
13849
normal! zo
13876
normal! zo
13890
normal! zo
13895
normal! zo
13935
normal! zo
13954
normal! zo
14022
normal! zo
14046
normal! zo
14097
normal! zo
14164
normal! zo
14172
normal! zo
14252
normal! zo
14302
normal! zo
14373
normal! zo
14399
normal! zo
14415
normal! zo
14486
normal! zo
14495
normal! zo
14531
normal! zo
14547
normal! zo
14561
normal! zo
14588
normal! zo
14592
normal! zo
14657
normal! zo
14664
normal! zo
14694
normal! zo
14697
normal! zo
14718
normal! zo
14757
normal! zo
14806
normal! zo
14836
normal! zo
14849
normal! zo
14865
normal! zo
14876
normal! zo
14902
normal! zo
14976
normal! zo
14991
normal! zo
14993
normal! zo
15048
normal! zo
15083
normal! zo
15129
normal! zo
15140
normal! zo
15178
normal! zo
15316
normal! zo
15331
normal! zo
15345
normal! zo
let s:l = 7188 - ((41 * winheight(0) + 24) / 49)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 7188
normal! 033|
wincmd w
argglobal
if bufexists(fnamemodify("verifier.c", ":p")) | buffer verifier.c | else | edit verifier.c | endif
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinscopedecls=public,protected,private
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal cursorlineopt=both
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal fillchars=
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
set foldlevel=99
setlocal foldlevel=99
setlocal foldmarker={{{,}}}
set foldmethod=syntax
setlocal foldmethod=syntax
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal listchars=
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,octal,hex
setlocal nonumber
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=8
setlocal noshortname
setlocal showbreak=
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal nosmartindent
setlocal nosmoothscroll
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal thesaurusfunc=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal virtualedit=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
1159
normal! zo
2741
normal! zo
2792
normal! zo
2851
normal! zo
2852
normal! zo
3784
normal! zo
3796
normal! zo
5375
normal! zo
5414
normal! zo
5834
normal! zo
5921
normal! zo
6136
normal! zo
7173
normal! zo
7365
normal! zo
9833
normal! zo
9835
normal! zo
9860
normal! zo
10234
normal! zo
10353
normal! zo
10890
normal! zo
10936
normal! zo
11036
normal! zo
11073
normal! zo
11164
normal! zo
11195
normal! zo
11409
normal! zo
11432
normal! zo
11645
normal! zo
12068
normal! zo
12077
normal! zo
12160
normal! zo
12283
normal! zo
12310
normal! zo
12407
normal! zo
12440
normal! zo
12454
normal! zo
12492
normal! zo
12494
normal! zo
12507
normal! zo
12534
normal! zo
12551
normal! zo
12576
normal! zo
12602
normal! zo
12621
normal! zo
12634
normal! zo
12651
normal! zo
12670
normal! zo
12713
normal! zo
12722
normal! zo
12729
normal! zo
12778
normal! zo
12811
normal! zo
12844
normal! zo
12911
normal! zo
12932
normal! zo
12962
normal! zo
12976
normal! zo
12991
normal! zo
13019
normal! zo
13036
normal! zo
13049
normal! zo
13075
normal! zo
13124
normal! zo
13176
normal! zo
13206
normal! zo
13232
normal! zo
13256
normal! zo
13278
normal! zo
13291
normal! zo
13298
normal! zo
13377
normal! zo
13387
normal! zo
13412
normal! zo
13437
normal! zo
13457
normal! zo
13499
normal! zo
13526
normal! zo
13565
normal! zo
13576
normal! zo
13617
normal! zo
13685
normal! zo
13687
normal! zo
13714
normal! zo
13737
normal! zo
13797
normal! zo
13819
normal! zo
13826
normal! zo
13827
normal! zo
13849
normal! zo
13876
normal! zo
13890
normal! zo
13895
normal! zo
13935
normal! zo
13954
normal! zo
14022
normal! zo
14046
normal! zo
14097
normal! zo
14164
normal! zo
14172
normal! zo
14252
normal! zo
14302
normal! zo
14373
normal! zo
14399
normal! zo
14415
normal! zo
14486
normal! zo
14495
normal! zo
14531
normal! zo
14547
normal! zo
14561
normal! zo
14588
normal! zo
14592
normal! zo
14657
normal! zo
14664
normal! zo
14694
normal! zo
14697
normal! zo
14718
normal! zo
14757
normal! zo
14806
normal! zo
14836
normal! zo
14849
normal! zo
14865
normal! zo
14876
normal! zo
14902
normal! zo
14976
normal! zo
14991
normal! zo
14993
normal! zo
15048
normal! zo
15083
normal! zo
15129
normal! zo
15140
normal! zo
15178
normal! zo
15316
normal! zo
15331
normal! zo
15345
normal! zo
12407
normal! zo
12440
normal! zo
12454
normal! zo
12492
normal! zo
12494
normal! zo
12507
normal! zo
12534
normal! zo
12551
normal! zo
12576
normal! zo
12602
normal! zo
12621
normal! zo
12634
normal! zo
12651
normal! zo
12670
normal! zo
12713
normal! zo
12722
normal! zo
12729
normal! zo
12778
normal! zo
12811
normal! zo
12844
normal! zo
12911
normal! zo
12932
normal! zo
12962
normal! zo
12976
normal! zo
12991
normal! zo
13019
normal! zo
13036
normal! zo
13049
normal! zo
13075
normal! zo
13124
normal! zo
13176
normal! zo
13206
normal! zo
13232
normal! zo
13256
normal! zo
13278
normal! zo
13291
normal! zo
13298
normal! zo
13377
normal! zo
13387
normal! zo
13412
normal! zo
13437
normal! zo
13457
normal! zo
13499
normal! zo
13526
normal! zo
13565
normal! zo
13576
normal! zo
13617
normal! zo
13685
normal! zo
13687
normal! zo
13714
normal! zo
13737
normal! zo
13797
normal! zo
13819
normal! zo
13826
normal! zo
13827
normal! zo
13849
normal! zo
13876
normal! zo
13890
normal! zo
13895
normal! zo
13935
normal! zo
13954
normal! zo
14022
normal! zo
14046
normal! zo
14097
normal! zo
14164
normal! zo
14172
normal! zo
14252
normal! zo
14302
normal! zo
14373
normal! zo
14399
normal! zo
14415
normal! zo
14486
normal! zo
14495
normal! zo
14531
normal! zo
14547
normal! zo
14561
normal! zo
14588
normal! zo
14592
normal! zo
14657
normal! zo
14664
normal! zo
14694
normal! zo
14697
normal! zo
14718
normal! zo
14757
normal! zo
14806
normal! zo
14836
normal! zo
14849
normal! zo
14865
normal! zo
14876
normal! zo
14902
normal! zo
14976
normal! zo
14991
normal! zo
14993
normal! zo
15048
normal! zo
15083
normal! zo
15129
normal! zo
15140
normal! zo
15178
normal! zo
15316
normal! zo
15331
normal! zo
15345
normal! zo
let s:l = 12312 - ((19 * winheight(0) + 24) / 49)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 12312
normal! 070|
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 49 + 50) / 101)
exe '2resize ' . ((&lines * 49 + 50) / 101)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
set shortmess=filnxtToOS
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
