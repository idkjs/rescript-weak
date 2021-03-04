type t('a);

let create: int => t('a);

let check: (t('a), int) => bool;

let get: (t('a), int) => option('a);

let set: (t('a), int, option('a)) => unit;

let blit: (t('a), int, t('a), int, int) => unit;

let length: t('a) => int;
