type weak('a);

type t('a) = array(option(weak('a)));

[@bs.new] external ext_make_weak : 'a => weak('a) = "WeakRef";

[@bs.send] external ext_deref : weak('a) => Js.Nullable.t('a) = "deref";

let deref = (w) => ext_deref(w) |> Js.Nullable.toOption;

let create = (i) => Array.init(i, (_) => None);

let check = (arr, i) =>
  arr[i]
  |. Belt.Option.map((x) => ext_deref(x) |> Js.Nullable.isNullable |> (!))
  |. Belt.Option.getWithDefault(false);

let get = (arr, i) => arr[i] |. Belt.Option.flatMap(deref);

let set = (arr, i, value) => Belt.Option.map(value, ext_make_weak) |> Array.set(arr, i);

let blit = (arr1, off1, arr2, off2, len) =>
  try (Array.blit(arr1, off1, arr2, off2, len)) {
  | Invalid_argument(_) => raise(Invalid_argument("Weak.blit"))
  };

let length = (arr) => Array.length(arr);
