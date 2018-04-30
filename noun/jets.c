/* g/j.c
**
*/
#include "all.h"

/**  Data structures.
**/

  /* _cj_hank: cached hook information.
   */
  typedef struct {
    u3_weak  hax;                     //  axis of hooked inner core
    u3j_site sit_u;                   //  call-site data
  } _cj_hank;

/**  Functions.
**/

  /* _cj_count(): count and link dashboard entries.
  */
  static c3_w 
  _cj_count(u3j_core* par_u, u3j_core* dev_u)
  {
    c3_w len_l = 0;
    c3_w i_w;

    if ( dev_u ) {
      for ( i_w = 0; 0 != dev_u[i_w].cos_c; i_w++ ) {
        u3j_core* kid_u = &dev_u[i_w];

        kid_u->par_u = par_u;
        len_l += _cj_count(kid_u, kid_u->dev_u);
      }
    }
    return 1 + len_l;
  }
  /* _cj_install(): install dashboard entries.
  */
  static c3_w
  _cj_install(u3j_core* ray_u, c3_w jax_l, u3j_core* dev_u)
  {
    c3_w i_w;

    if ( dev_u ) {
      for ( i_w = 0; 0 != dev_u[i_w].cos_c; i_w++ ) {
        u3j_core* kid_u = &dev_u[i_w];

        kid_u->jax_l = jax_l;
        ray_u[jax_l++] = *kid_u;

        jax_l = _cj_install(ray_u, jax_l, kid_u->dev_u);
      }
    }
    return jax_l;
  }

/* _cj_axis(): axis from formula, or 0.  `fol` is RETAINED.
*/
static c3_l
_cj_axis(u3_noun fol)
{
  u3_noun p_fol, q_fol, r_fol;

  while ( _(u3du(fol)) && (10 == u3h(fol)) )
    { fol = u3t(u3t(fol)); }

  if ( !_(u3r_trel(fol, &p_fol, &q_fol, &r_fol)) ) {
    if ( !_(u3r_cell(fol, &p_fol, &q_fol)) ||
         (0 != p_fol) ||
         (!_(u3a_is_cat(q_fol))) )
    { 
      fprintf(stderr, "axis: bad a\r\n"); 
      return 0;
    }
    return q_fol;
  }
  else {
    if ( 9 != p_fol )
      { fprintf(stderr, "axis: bad b\r\n"); return 0; }
    if ( !_(u3a_is_cat(q_fol)) )
      { fprintf(stderr, "axis: bad c\r\n"); return 0; }
    if ( !_(u3du(r_fol)) || (0 != u3h(r_fol)) || (1 != u3t(r_fol)) )
      { fprintf(stderr, "axis: bad d\r\n"); return 0; }

    return q_fol;
  }
}

#if 0
/* _cj_by_gut(): (~(get by a) b), unifying; RETAINS a, b, AND result.
*/
static u3_weak
_cj_by_gut(u3_noun a, u3_noun b)
{
  if ( u3_nul == a ) {
    return u3_none;
  }
  else {
    u3_noun l_a, n_a, r_a;
    u3_noun pn_a, qn_a;

    u3x_trel(a, &n_a, &l_a, &r_a);
    u3x_cell(n_a, &pn_a, &qn_a);
    {
      if ( (c3y == u3r_sing(b, pn_a)) ) {
        return qn_a;
      }
      else {
        if ( c3y == u3qc_gor(b, pn_a) ) {
          return _cj_by_gut(l_a, b);
        }
        else return _cj_by_gut(r_a, b);
      }
    }
  }
}
#endif

/* _cj_chum(): decode chum as string.
*/
static c3_c* 
_cj_chum(u3_noun chu)
{
  if ( _(u3ud(chu)) ) {
    return u3r_string(chu);
  } 
  else {
    u3_noun h_chu = u3h(chu);
    u3_noun t_chu = u3t(chu);
    
    if ( !_(u3a_is_cat(t_chu)) ) {
      return 0;
    } else {
      c3_c* h_chu_c = u3r_string(h_chu);
      c3_c  buf[33];

      memset(buf, 0, 33);
      snprintf(buf, 32, "%s%d", h_chu_c, t_chu);

      free(h_chu_c);
      return strdup(buf);
    }
  }
}

/* _cj_je_fsck: fsck:je, or none.
*/
static u3_noun
_cj_je_fsck(u3_noun clu)
{
  u3_noun     p_clu, q_clu, r_clu;
  u3_noun     huk;
  c3_c*       nam_c;
  c3_l        axe_l;

  if ( c3n == u3r_trel(clu, &p_clu, &q_clu, &r_clu) ) {
    u3z(clu); return u3_none;
  }
  if ( 0 == (nam_c = _cj_chum(p_clu)) ) {
    u3z(clu); return u3_none;
  }
  while ( _(u3du(q_clu)) && (10 == u3h(q_clu)) ) { 
    q_clu = u3t(u3t(q_clu));
  }
  if ( !_(u3du(q_clu)) ) {
    u3z(clu); free(nam_c); return u3_none;
  }

  if ( (1 == u3h(q_clu)) && (0 == u3t(q_clu)) ) {
    axe_l = 0;
  }
  else {
    if ( (0 != u3h(q_clu)) || !_(u3a_is_cat(axe_l = u3t(q_clu))) ) {
      u3z(clu); free(nam_c); return u3_none;
    }
  }

  {
    huk = 0;

    while ( _(u3du(r_clu)) ) {
      u3_noun ir_clu, tr_clu, pir_clu, qir_clu;

      if ( (c3n == u3r_cell(r_clu, &ir_clu, &tr_clu)) ||
           (c3n == u3r_cell(ir_clu, &pir_clu, &qir_clu)) ||
           (c3n == u3ud(pir_clu)) )
      {
        u3z(huk); u3z(clu); free(nam_c); return u3_none;
      }
      huk = u3kdb_put(huk, u3k(pir_clu), u3k(qir_clu));
      r_clu = tr_clu;
    }
  }
  u3z(clu);
  return u3nt(u3i_string(nam_c), axe_l, huk);
}

/* _cj_find_cold(): search cold state for `bat`s registry.
 *                  RETAIN.
 */
static u3_weak
_cj_find_cold(u3_noun bat)
{
  u3a_road* rod_u = u3R;

  while ( 1 ) {
    u3_weak reg = u3h_gut(rod_u->jed.cod_p, bat);

    if ( u3_none != reg ) {
      return reg;
    }

    if ( rod_u->par_p ) {
      rod_u = u3to(u3_road, rod_u->par_p);
    }
    else return u3_none;
  }
}

/* _cj_find_warm(): search warm state for `loc`s activation.
 *                  RETAIN.
 */
static u3_weak
_cj_find_warm(u3_noun loc)
{
  u3a_road* rod_u = u3R;

  while ( 1 ) {
    u3_weak ank = u3h_gut(rod_u->jed.war_p, loc);

    if ( u3_none != ank ) {
      return ank;
    }

    if ( rod_u->par_p ) {
      rod_u = u3to(u3_road, rod_u->par_p);
    }
    else return u3_none;
  }
}

/* _cj_spot(): find location of cor. expensive. cor is RETAINED.
 */
static u3_weak
_cj_spot(u3_noun cor)
{
  u3_weak reg = _cj_find_cold(u3h(cor));
  if ( u3_none == reg ) {
    return u3_none;
  }
  else {
    u3_noun rut = u3h(reg),
            pas = u3t(reg),
            rum = u3qdb_get(rut, u3t(cor));
    if ( u3_nul != rum ) {
      u3_noun loc = u3k(u3t(rum));
      u3z(rum); u3z(reg);
      return loc;
    }
    else {
      while ( u3_nul != pas ) {
        u3_noun pap = u3h(pas),
                axe = u3h(pap),
                lol = u3t(pap);
        u3_weak par = u3r_at(axe, cor),
                pel;
        if ( u3_none != par ) {
          pel = _cj_spot(par);
          if ( u3_none != pel ) {
            u3_noun nit = u3qdb_get(lol, pel);
            u3z(pel);
            if ( u3_nul != nit ) {
              u3_noun loc = u3k(u3t(nit));
              u3z(nit); u3z(reg);
              return loc;
            }
          }
        }
        pas = u3t(pas);
      }
      u3z(reg);
      return u3_none;
    }
  }
}

/* _cj_cast(): create a u3j_fink that can be used to efficiently verify
 *             that another core is located where this one is.
 */
static u3p(u3j_fink)
_cj_cast(u3_noun cor, u3_noun loc)
{
  c3_w     i_w = 0;
  u3_noun  j, par, bat, dyn, pax,
           rev = u3_nul,
           pat = u3h(loc);
  u3j_fink* fin_u;

  while ( c3n == u3h(pat) ) {
    bat = u3h(cor);
    dyn = u3t(pat);
    pax = u3h(dyn);
    loc = u3t(dyn);
    pat = u3h(loc);
    rev = u3nc(u3nc(u3k(bat), u3k(pax)), rev);
    cor = u3r_at(pax, cor);
    ++i_w;
  }

  fin_u = u3a_walloc(c3_wiseof(u3j_fink) +
                     (i_w * c3_wiseof(u3j_fist)));
  fin_u->len_w = i_w;
  fin_u->sat   = u3k(cor);
  for ( j = rev; i_w-- > 0; j = u3t(j) ) {
    u3j_fist* fis_u = &(fin_u->fis_u[i_w]);
    par        = u3h(j);
    fis_u->bat = u3k(u3h(par));
    fis_u->pax = u3k(u3t(par));
  }
  u3z(rev);
  c3_assert( u3_nul == j );

  return u3of(u3j_fink, fin_u);
}

/* _cj_fine(): check that a core matches a u3j_fink
 */
static c3_o
_cj_fine(u3_noun cor, u3p(u3j_fink) fin_p)
{
  u3j_fink* fin_u = u3to(u3j_fink, fin_p);
  c3_w i_w;
  for ( i_w = 0; i_w < fin_u->len_w; ++i_w ) {
    u3j_fist* fis_u = &(fin_u->fis_u[i_w]);
    if ( c3n == u3r_sing(fis_u->bat, u3h(cor)) ) {
      return c3n;
    }
    else {
      cor = u3r_at(fis_u->pax, cor);
    }
  }
  return u3r_sing(fin_u->sat, cor);
}

/* _cj_nail(): resolve hot state for arm at axis within cores located
 *             at loc. a label will be PRODUCED at *lab, unconditionally.
 *             Arguments are RETAINED. Return value is yes if a jet driver
 *             is present.
 */
static c3_o
_cj_nail(u3_noun loc, u3_noun axe,
         u3_noun* lab, u3j_core** cop_u, u3j_harm** ham_u)
{
  c3_o ret_o;
  u3_noun jax, hap, bal, jit;
  u3_weak act;
  act = _cj_find_warm(loc);
  c3_assert(u3_none != act);
  u3x_qual(act, &jax, &hap, &bal, &jit);

  *lab = u3k(bal);
  if ( 0 == jax ) {
    ret_o = c3n;
  }
  else {
    u3_weak inx = u3kdb_get(u3k(hap), u3k(axe));
    if ( u3_none == inx ) {
      ret_o = c3n;
    }
    else {
      c3_l jax_l = jax,
           inx_l = inx;
      *cop_u = &(u3D.ray_u[jax_l]);
      *ham_u = &((*cop_u)->arm_u[inx_l]);
      ret_o = c3y;
    }
  }

  u3z(act);
  return ret_o;
}

/* _cj_scan(): has this core been registered?  RETAIN.
 */
static c3_o
_cj_scan(u3_noun cor)
{
  u3_weak loc = _cj_spot(cor);
  c3_o  reg_o = (u3_none == loc) ? c3n : c3y;
  u3z(loc);
  return reg_o;
}

/* _cj_warm_hump(): generate axis-to-arm map.  RETAIN.
*/
static u3_noun
_cj_warm_hump(c3_l jax_l, u3_noun huc)
{
  u3_noun     hap = u3_nul;
  u3j_core* cop_u;

  /* Compute axes of all correctly declared arms.
  */
  if ( jax_l && (cop_u = &u3D.ray_u[jax_l])->arm_u ) {
    u3j_harm* jet_u;
    c3_l        i_l;

    for ( i_l = 0; (jet_u = &cop_u->arm_u[i_l])->fcs_c; i_l++ ) {
      c3_l axe_l = 0;

      if ( '.' == *(jet_u->fcs_c) ) {
        c3_d axe_d = 0;

        if ( (1 != sscanf(jet_u->fcs_c+1, "%" SCNu64, &axe_d)) ||
             axe_d >> 32ULL ||
             ((1 << 31) & (axe_l = (c3_w)axe_d)) ||
             (axe_l < 2) )
        {
          fprintf(stderr, "jets: activate: bad fcs %s\r\n", jet_u->fcs_c);
        }
      }
      else {
        u3_noun nam = u3i_string(jet_u->fcs_c);
        u3_noun fol = u3kdb_get(u3k(huc), nam);

        if ( u3_none == fol ) {
          fprintf(stderr, "jets: activate: bad fcs %s\r\n", jet_u->fcs_c);
        }
        else {
          axe_l = _cj_axis(fol);
          u3z(fol);
        }
      }
      if ( 0 != axe_l ) {
        hap = u3kdb_put(hap, axe_l, i_l);
      }
    }
  }
  return hap;
}

/* _cj_hot_mean(): in parent, declare a core.  RETAINS.
*/
static c3_l
_cj_hot_mean(c3_l par_l, u3_noun nam)
{
  u3j_core* par_u;
  u3j_core* dev_u;

  if ( 0 != par_l ) {
    par_u = &u3D.ray_u[par_l];
    dev_u = par_u->dev_u;
  }
    else {
    par_u = 0;
    dev_u = u3D.dev_u;
  }

  {
    c3_w i_l = 0;
    u3j_core* cop_u;

    while ( (cop_u = &dev_u[i_l])->cos_c ) {
      if ( _(u3r_sing_c(cop_u->cos_c, nam)) ) {
#if 0
        fprintf(stderr, "hot: bound jet %d/%s/%s/\r\n", 
                        cop_u->jax_l, 
                        cop_u->cos_c,
                        par_u ? par_u->cos_c : "~");
#endif
        return cop_u->jax_l;
      }
      i_l++;
    }
  }
  return 0;
}

/* u3j_boot(): initialize jet system.
*/
void
u3j_boot(void)
{
  c3_w jax_l;

  u3D.len_l =_cj_count(0, u3D.dev_u);
  u3D.all_l = (2 * u3D.len_l) + 1024;     //  horrid heuristic

  u3D.ray_u = (u3j_core*) malloc(u3D.all_l * sizeof(u3j_core));
  memset(u3D.ray_u, 0, (u3D.all_l * sizeof(u3j_core)));

  jax_l = _cj_install(u3D.ray_u, 1, u3D.dev_u);
  fprintf(stderr, "boot: installed %d jets\n", jax_l);
}

/* _cj_soft(): kick softly by arm axis.
*/
static u3_noun
_cj_soft(u3_noun cor, u3_noun axe)
{
  u3_noun arm = u3x_at(axe, cor);

  return u3n_nock_on(cor, u3k(arm));
}

  void
  find_error(u3_noun cor,
             u3_noun old,
             u3_noun new);

/* _cj_kick_z(): try to kick by jet.  If no kick, produce u3_none.
**
** `cor` is RETAINED iff there is no kick, TRANSFERRED if one.  
** `axe` is RETAINED.
*/
static u3_weak
_cj_kick_z(u3_noun cor, u3j_core* cop_u, u3j_harm* ham_u, u3_atom axe)
{
  if ( 0 == ham_u->fun_f ) {
    return u3_none;
  }

  if ( !_(ham_u->liv) ) {
    return u3_none;
  }
  else {
#ifdef U3_MEMORY_DEBUG
    c3_w cod_w;

    {
      char soc_c[6];

      memset(soc_c, 0, 6);
      strncpy(soc_c, cop_u->cos_c, 5);
      soc_c[5] = 0;
      cod_w = u3i_string(soc_c);

      cod_w = u3a_lush(cod_w);
    }
#endif

    if ( _(ham_u->ice) ) {
      u3_weak pro = ham_u->fun_f(cor);

#ifdef U3_MEMORY_DEBUG
      u3a_lop(cod_w);
#endif
      if ( u3_none != pro ) {
        u3z(cor);
        return pro;
      }
    }
    else {
      u3_weak pro, ame;

      ham_u->ice = c3y;
      pro = ham_u->fun_f(u3k(cor));
      ham_u->ice = c3n;

#ifdef U3_MEMORY_DEBUG
      u3a_lop(cod_w);
#endif
      if ( u3_none == pro ) {
        u3z(cor);
        return pro;
      }
      ham_u->liv = c3n;
      ame = _cj_soft(cor, axe);
      ham_u->liv = c3y;

      if ( c3n == u3r_sing(ame, pro) ) {
        fprintf(stderr, "test: %s %s: mismatch: good %x, bad %x\r\n",
               cop_u->cos_c,
               (!strcmp(".2", ham_u->fcs_c)) ? "$" : ham_u->fcs_c,
               u3r_mug(ame), 
               u3r_mug(pro));
        ham_u->liv = c3n;

        c3_assert(0);
        return u3m_bail(c3__fail);
      }
      else {

#if 0
        fprintf(stderr, "test: %s %s\r\n",
               cop_u->cos_c,
               (!strcmp(".2", ham_u->fcs_c)) ? "$" : ham_u->fcs_c);
#endif
        u3z(ame);
        return pro;
      }
    }
    return u3_none;
  }
}

/* _cj_hook_in(): execute hook from core, or fail.
*/
static u3_noun
_cj_hook_in(u3_noun     cor,
            const c3_c* tam_c,
            c3_o        jet_o)
{
  u3_weak   loc, col;
  u3_noun   roc, tem, got, pat, nam, huc;

  if ( c3n == u3du(cor) ) {
    return u3m_bail(c3__fail);
  }

  loc = _cj_spot(cor);
  if ( u3_none == loc ) {
    return u3m_bail(c3__fail);
  }

  tem = u3i_string(tam_c);
  while ( 1 ) {
    u3x_trel(loc, &pat, &nam, &huc);
    got = u3qdb_get(huc, tem);
    if ( u3_nul != got ) {
      c3_l axe_l;
      u3_noun pro, fol;
      u3j_core* cop_u;

      u3z(tem);
      fol = u3k(u3t(got));
      u3z(got);
      axe_l = _cj_axis(fol);
      if ( 0 == axe_l ) {
        u3t_off(glu_o);
        pro = u3n_nock_on(cor, fol);
        u3t_on(glu_o);
      }
      else {
        c3_l jax_l, inx_l;
        u3_noun hap, act;

        u3z(fol);
        act   = _cj_find_warm(loc);
        jax_l = u3h(act);
        hap   = u3h(u3t(act));
        cop_u = &u3D.ray_u[jax_l];

        //  Tricky: the above case would work here too, but would
        //  disable jet_o and create some infinite recursions.
        //
        u3t_off(glu_o);
        if ( (c3n == jet_o) ||
             (u3_none == (inx_l = u3kdb_get(u3k(hap), axe_l))) ||
             (u3_none == (pro = _cj_kick_z(cor,
                                           cop_u,
                                           &cop_u->arm_u[inx_l],
                                           axe_l))) ) {
          pro = u3n_nock_on(cor, u3k(u3x_at(axe_l, cor)));
        }
        u3t_on(glu_o);
        u3z(act);
      }
      u3z(loc);
      return pro;
    }
    else if ( c3n == u3h(pat) ) {
      u3_noun dyn = u3t(pat),
              axe = u3h(dyn),
              pel = u3t(dyn);
      roc = u3k(u3r_at(axe, cor));
      u3z(cor);
      cor = roc;
      col = u3k(pel);
      u3z(loc);
      loc = col;
    }
    else {
      u3_noun sat = u3t(pat);
      if ( c3y == u3h(sat) ) {
        return u3m_bail(c3__fail);
      }
      else {
        col = u3k(u3t(sat));
        u3z(loc);
        loc = col;
        roc = u3k(u3t(cor));
        u3z(cor);
        cor = roc;
      }
    }
  }
}

/* u3j_soft(): execute soft hook.
*/
u3_noun
u3j_soft(u3_noun cor, 
         const c3_c* tam_c)
{
  u3_noun pro;
  u3t_on(glu_o);
  pro = _cj_hook_in(cor, tam_c, c3n);
  u3t_off(glu_o);
  return pro;
}

/* u3j_hook(): execute hook from core, or fail.
*/
u3_noun
u3j_hook(u3_noun     cor,
         const c3_c* tam_c)
{
  u3_noun pro;
  u3t_on(glu_o);
  pro = _cj_hook_in(cor, tam_c, c3y);
  u3t_off(glu_o);
  return pro;
}

/* _cj_prog(): stop tracing glu and find a nock program
 */
static u3p(u3n_prog)
_cj_prog(u3_noun fol)
{
  u3p(u3n_prog) pog_p;
  u3t_off(glu_o);
  pog_p = u3n_find(fol);
  u3t_on(glu_o);
  return pog_p;
}

/* cj_hank_find(): find cached hook information, keyed by arbitrary
 *                 prefix and term cords. RETAIN.
 */
static _cj_hank*
_cj_hank_find(u3_noun pre, u3_noun tam)
{
  u3_noun key = u3nc(u3k(pre), u3k(tam));
  u3_noun got = u3h_git(u3R->jed.han_p, key);
  if ( u3_none != got ) {
    u3z(key);
    return u3to(_cj_hank, got);
  }
  else {
    _cj_hank* new_u = u3a_walloc(c3_wiseof(_cj_hank));
    u3a_road* rod_u = u3R;
    while ( rod_u->par_p && u3_none == got ) {
      rod_u = u3to(u3a_road, rod_u->par_p);
      got   = u3h_git(u3R->jed.han_p, key);
    }
    if ( u3_none == got ) {
      new_u->hax = u3_none;
    }
    else {
      _cj_hank* old_u = u3to(_cj_hank, got);
      if ( u3_none != (new_u->hax = old_u->hax) ) {
        u3j_site_copy(&(new_u->sit_u), &(old_u->sit_u), c3n);
      }
    }
    u3h_put(u3R->jed.han_p, key, u3a_outa(new_u));
    u3z(key);
    return new_u;
  }
}

/* _cj_hank_fine(): check that cached hook information is valid
 *                  for given core. *inn will point to the hooked
 *                  core on return if valid. RETAIN.
 */
static c3_o
_cj_hank_fine(_cj_hank* han_u, u3_noun cor, u3_noun *inn)
{
  u3_noun hax = han_u->hax;
  if ( u3_none == hax ) {
    return c3n;
  }
  else {
    *inn = u3r_at(hax, cor);
    if ( u3_none == *inn ) {
      return c3n;
    }
    else {
      u3j_site* sit_u = &(han_u->sit_u);
      c3_assert(u3_none != sit_u->loc);
      return _cj_fine(*inn, sit_u->fin_p);
    }
  }
}

/* _cj_hank_lose(): release memory maintained in a hook cache.
*/
static void
_cj_hank_lose(_cj_hank* han_u)
{
  if ( u3_none != han_u->hax ) {
    u3z(han_u->hax);
    u3j_site_lose(&(han_u->sit_u));
  }
}

/* _cj_hank_fill(): slow path, populate han_u.
 */
static u3_noun
_cj_hank_fill(_cj_hank* han_u, u3_noun tam, u3_noun cor)
{
  u3_weak   loc, col;
  u3_noun   got, pat, nam, huc;
  u3_noun   hax = 1;
  u3j_site* sit_u = &(han_u->sit_u);

  if ( c3n == u3du(cor) ) {
    return u3m_bail(c3__fail);
  }

  if ( u3_none == (col = loc = _cj_spot(cor)) ) {
    return u3m_bail(c3__fail);
  }

  while ( 1 ) {
    u3x_trel(loc, &pat, &nam, &huc);
    got = u3qdb_get(huc, tam);
    if ( u3_nul != got ) {
      u3_noun fol = u3k(u3t(got));
      u3z(got);
      sit_u->bat   = u3k(u3h(cor));
      sit_u->loc   = u3k(loc);
      sit_u->fin_p = _cj_cast(cor, loc);
      sit_u->fon_o = c3y;
      if ( 0 == (sit_u->axe = _cj_axis(fol)) ) {
        sit_u->jet_o = c3n;
        sit_u->pog_p = _cj_prog(fol);
      }
      else {
        han_u->sit_u.pog_p = _cj_prog(u3r_at(sit_u->axe, cor));
        han_u->sit_u.jet_o = _cj_nail(loc, sit_u->axe,
            &(sit_u->lab), &(sit_u->cop_u), &(sit_u->ham_u));
      }
      u3z(fol);
      u3z(col);
      han_u->hax = hax;
      return cor;
    }
    else if ( c3n == u3h(pat) ) {
      u3_noun dyn = u3t(pat),
              axe = u3h(dyn),
              xah;
      cor = u3r_at(axe, cor);
      loc = u3t(dyn);
      xah = u3qc_peg(axe, hax);
      u3z(hax);
      hax = xah;
    }
    else {
      u3_noun sat = u3t(pat);
      if ( c3y == u3h(sat) ) {
        return u3m_bail(c3__fail);
      }
      else {
        u3_noun xah;
        cor = u3t(cor);
        loc = u3t(sat);
        xah = u3qc_peg(3, hax);
        u3z(hax);
        hax = xah;
      }
    }
  }
}

/* u3j_kick(): new kick.
**
** `axe` is RETAINED by the caller; `cor` is RETAINED iff there 
** is no kick, TRANSFERRED if one.
*/
u3_weak
u3j_kick(u3_noun cor, u3_noun axe)
{
  u3t_on(glu_o);
  u3_weak loc = _cj_spot(cor);
  if ( u3_none == loc ) {
    u3t_off(glu_o);
    return u3_none;
  }
  else {
    u3_weak act = _cj_find_warm(loc);
    u3z(loc);
    if ( u3_none == act ) {
      u3t_off(glu_o);
      return u3_none;
    }
    else {
      c3_l jax_l;
      u3_noun hap, bal, jit, inx;

      u3x_qual(act, &jax_l, &hap, &bal, &jit);

      if ( u3_none == (inx = u3kdb_get(u3k(hap), u3k(axe))) ) {
        u3t_off(glu_o); 
        {
          c3_o pof_o = __(u3C.wag_w & u3o_debug_cpu);

          if ( _(pof_o) ) {
            pof_o = u3t_come(bal);
          }
          u3z(act);
          if ( _(pof_o) ) {
            u3_noun pro = u3n_nock_on(cor, u3nq(9, u3k(axe), 0, 1));

            u3t_flee();
            return pro;
          }
          else {
            return u3_none;
          }
        }
      }
      else {
        u3j_core* cop_u = &u3D.ray_u[jax_l];
        c3_l      inx_l = inx;
        u3j_harm* ham_u = &cop_u->arm_u[inx_l];
        c3_o      pof_o = __(u3C.wag_w & u3o_debug_cpu);
        u3_noun   pro;

        if ( _(pof_o) ) {
          pof_o = u3t_come(bal);
        }
        u3z(act);
        u3t_off(glu_o);
        pro = _cj_kick_z(cor, cop_u, ham_u, axe);
 
        if ( u3_none == pro ) {
          if ( _(pof_o) ) {
            pro = u3n_nock_on(cor, u3nq(9, u3k(axe), 0, 1));

            u3t_flee();
            return pro;
          } 
          else return u3_none;
        }
        else {
          if ( _(pof_o) ) {
            u3t_flee();
          }
          return pro;
        }
      }
    }
  }
}

/* _cj_fink_take(): copy u3j_fink from junior road.
*/
static u3j_fink*
_cj_fink_take(u3j_fink* jun_u)
{
  c3_w     i_w, len_w = jun_u->len_w;
  u3j_fink* fin_u = u3a_walloc(c3_wiseof(u3j_fink) +
                   (len_w * c3_wiseof(u3j_fist)));

  fin_u->len_w = len_w;
  fin_u->sat   = u3a_take(jun_u->sat);
  for ( i_w = 0; i_w < len_w; ++i_w ) {
    u3j_fist* fis_u = &(fin_u->fis_u[i_w]);
    u3j_fist* sif_u = &(jun_u->fis_u[i_w]);
    fis_u->bat = u3a_take(sif_u->bat);
    fis_u->pax = u3a_take(sif_u->pax);
  }
  return fin_u;
}

/* _cj_fink_free(): lose and free everything in a u3j_fink.
*/
static void
_cj_fink_free(u3p(u3j_fink) fin_p)
{
  c3_w i_w;
  u3j_fink* fin_u = u3to(u3j_fink, fin_p);
  u3z(fin_u->sat);
  for ( i_w = 0; i_w < fin_u->len_w; ++i_w ) {
    u3j_fist* fis_u = &(fin_u->fis_u[i_w]);
    u3z(fis_u->bat);
    u3z(fis_u->pax);
  }
  u3a_wfree(fin_u);
}

/* u3j_rite_copy(): copy rite references from src_u to dst_u,
**                  losing old references if los_o is yes
*/
void
u3j_rite_copy(u3j_rite* dst_u, u3j_rite* src_u, c3_o los_o)
{
  if ( u3_none == src_u->clu ) {
    dst_u->clu   = u3_none;
    dst_u->fin_p = 0;
  }
  else {
    u3p(u3j_fink) fon_p = dst_u->fin_p;
    u3_noun   old   = dst_u->clu;
    c3_o      own_o = dst_u->own_o;
    if ( c3y == src_u->own_o ) {
      dst_u->own_o = c3y;
      dst_u->clu   = u3a_take(src_u->clu);
      dst_u->fin_p = u3of(u3j_fink, _cj_fink_take(u3to(u3j_fink, src_u->fin_p)));
      if ( (c3y == los_o) &&
          (u3_none != old) &&
          (c3y == own_o) ) {
        u3z(old);
        _cj_fink_free(fon_p);
      }
    }
  }
}

/* u3j_site_copy(): copy site references from src_u to dst_u,
**                  losing old references if los_o is yes
*/
void
u3j_site_copy(u3j_site* dst_u, u3j_site* src_u, c3_o los_o)
{
  u3_noun old = dst_u->axe;
  dst_u->axe  = u3a_take(src_u->axe);

  if ( c3y == los_o ) {
    u3z(old);
  }
  else {
    dst_u->bat   = u3_none;
    dst_u->pog_p = 0;
    dst_u->loc   = u3_none;
    dst_u->lab   = u3_none;
    dst_u->jet_o = c3n;
    dst_u->fon_o = c3n;
    dst_u->cop_u = NULL;
    dst_u->ham_u = NULL;
    dst_u->fin_p = 0;
  }

  if ( u3_none != src_u->loc ) {
    u3_noun  lob   = dst_u->lab,
             lod   = dst_u->loc;
    c3_o     fon_o = dst_u->fon_o;
    u3p(u3j_fink) fon_p = dst_u->fin_p;

    dst_u->loc   = u3a_take(src_u->loc);
    dst_u->lab   = u3a_take(src_u->lab);
    dst_u->cop_u = src_u->cop_u;
    dst_u->ham_u = src_u->ham_u;
    dst_u->jet_o = src_u->jet_o;

    if ( c3y == src_u->fon_o ) {
      dst_u->fin_p = u3of(u3j_fink, _cj_fink_take(u3to(u3j_fink, src_u->fin_p)));
      dst_u->fon_o = c3y;
    }
    else if ( fon_p != src_u->fin_p ) {
      dst_u->fin_p = src_u->fin_p;
      dst_u->fon_o = c3n;
    }
    else {
      fon_o = c3n;
    }

    if ( c3y == los_o ) {
      if ( u3_none != lod ) {
        u3z(lod);
        u3z(lob);
        if ( c3y == fon_o ) {
          _cj_fink_free(fon_p);
        }
      }
    }
  }
}

/* u3j_site_ream(): refresh u3j_site after restoring from checkpoint
*/
void
u3j_site_ream(u3j_site* sit_u)
{
  if ( u3_none != sit_u->loc ) {
    u3z(sit_u->lab);
    sit_u->jet_o = _cj_nail(sit_u->loc, sit_u->axe,
        &(sit_u->lab), &(sit_u->cop_u), &(sit_u->ham_u));
  }
}

/* _cj_site_lock(): ensure site has a valid program pointer
 */
static void
_cj_site_lock(u3_noun cor, u3j_site* sit_u)
{
  if ( (u3_none != sit_u->bat) &&
       (c3y == u3r_sing(sit_u->bat, u3h(cor))) ) {
    return;
  }
  sit_u->pog_p = _cj_prog(u3r_at(sit_u->axe, cor));
  if ( u3_none != sit_u->bat ) {
    u3z(sit_u->bat);
  }
  sit_u->bat = u3k(u3h(cor));
}

/* _cj_burn(): stop tracing glu and call a nock program
 */
static u3_noun
_cj_burn(u3p(u3n_prog) pog_p, u3_noun cor)
{
  u3_noun pro;
  u3t_off(glu_o);
  pro = u3n_burn(pog_p, cor);
  u3t_on(glu_o);
  return pro;
}

/* _cj_site_kick_hot(): execute site's kick on located core
**                      (no validity checks).
*/
static u3_weak
_cj_site_kick_hot(u3_noun cor, u3j_site* sit_u)
{
  u3_weak pro = u3_none;
  c3_o jet_o  = sit_u->jet_o;
  c3_o pof_o  =  __(u3C.wag_w & u3o_debug_cpu);
  if ( c3n == pof_o ) {
    if ( c3n == jet_o ) {
      pro = u3_none;
    }
    else {
      u3t_off(glu_o);
      pro = _cj_kick_z(cor, sit_u->cop_u, sit_u->ham_u, sit_u->axe);
      u3t_on(glu_o);
    }
    if ( u3_none == pro ) {
      _cj_site_lock(cor, sit_u);
    }
  }
  else {
    pof_o = u3t_come(sit_u->lab);
    if ( c3y == jet_o ) {
      u3t_off(glu_o);
      pro = _cj_kick_z(cor, sit_u->cop_u, sit_u->ham_u, sit_u->axe);
      u3t_on(glu_o);
    }
    if ( u3_none == pro ) {
      _cj_site_lock(cor, sit_u);
      pro = _cj_burn(sit_u->pog_p, cor);
    }
    if ( c3y == pof_o ) {
      u3t_flee();
    }
  }
  return pro;
}

/* _cj_site_kick(): execute site's kick on core.
 */
static u3_weak
_cj_site_kick(u3_noun cor, u3j_site* sit_u)
{
  u3_weak loc, pro;

  loc = pro = u3_none;

  if ( u3_none != sit_u->loc ) {
    if ( c3y == _cj_fine(cor, sit_u->fin_p) ) {
      loc = sit_u->loc;
      if ( c3y == sit_u->jet_o ) {
        pro = _cj_site_kick_hot(cor, sit_u);
      }
    }
  }

  if ( u3_none == loc ) {
    loc = _cj_spot(cor);
    if ( u3_none != loc ) {
      u3p(u3j_fink) fon_p = 0;
      u3_weak  lod   = u3_none;
      u3_weak  lob   = u3_none;

      if ( u3_none != sit_u->loc ) {
        lod = sit_u->loc;
        lob = sit_u->lab;
        if ( c3y == sit_u->fon_o ) {
          fon_p = sit_u->fin_p;
        }
      }

      sit_u->loc   = loc;
      sit_u->fin_p = _cj_cast(cor, loc);
      sit_u->fon_o = c3y;
      if ( c3y ==
        (sit_u->jet_o = _cj_nail(loc, sit_u->axe,
            &(sit_u->lab), &(sit_u->cop_u), &(sit_u->ham_u))) )
      {
        pro = _cj_site_kick_hot(cor, sit_u);
      }
      else {
        pro = u3_none;
      }

      if ( u3_none != lod ) {
        u3z(lod);
        u3z(lob);
        if ( 0 != fon_p ) {
          _cj_fink_free(fon_p);
        }
      }
    }
  }

  if ( u3_none == pro ) {
    _cj_site_lock(cor, sit_u);
  }

  return pro;
}

/* u3j_site_kick(): kick a core with a u3j_site cache.
 */
u3_weak
u3j_site_kick(u3_noun cor, u3j_site* sit_u)
{
  u3_weak pro;
  u3t_on(glu_o);
  pro = _cj_site_kick(cor, sit_u);
  u3t_off(glu_o);
  return pro;
}

/* u3j_cook(): Execute hook from core, call site cached by arbitrary c string
*/
u3_noun
u3j_cook(const c3_c* key_c,
         u3_noun     cor,
         const c3_c* tam_c)
{
  u3_noun pro, key, tam, inn;
  _cj_hank* han_u;

  u3t_on(glu_o);
  key = u3i_string(key_c);
  tam = u3i_string(tam_c);
  han_u = _cj_hank_find(key, tam);
  if ( c3n == _cj_hank_fine(han_u, cor, &inn) ) {
    _cj_hank_lose(han_u);
    inn = _cj_hank_fill(han_u, tam, cor);
  }
  pro = _cj_site_kick(u3k(inn), &(han_u->sit_u));
  if ( u3_none == pro ) {
    pro = _cj_burn(han_u->sit_u.pog_p, inn);
  }
  u3z(cor);
  
  u3z(key);
  u3z(tam);
  u3t_off(glu_o);
  return pro;
}

/* u3j_kink(): kick either by jet or by nock.
*/
u3_noun
u3j_kink(u3_noun cor, u3_noun axe)
{
  u3_weak pro = u3j_kick(cor, axe);

  if ( u3_none != pro ) {
    return pro;
  }
  else {
    u3_weak fol = u3r_at(axe, cor);
    if ( u3_none == fol ) {
      return u3m_bail(c3__exit);
    }
    else {
      return u3n_nock_on(cor, u3k(fol));
    }
  }
}

/* u3j_gate_prep(): prepare a locally cached gate to call repeatedly.
 *                  core is TRANSFERRED.
 */
void
u3j_gate_prep(u3j_site* sit_u, u3_noun cor)
{
  u3_noun loc;
  u3t_on(glu_o);
  if ( c3n == u3du(cor) || c3n == u3du(u3t(cor)) ) {
    u3m_bail(c3__exit);
    return;
  }
  sit_u->axe   = 2;
  sit_u->bat   = cor; // a lie, this isn't really the battery!
  sit_u->pog_p = _cj_prog(u3h(cor));
  if ( u3_none != (loc = sit_u->loc = _cj_spot(cor)) ) {
    u3_noun pax = u3h(u3t(loc)),
            pay = u3qc_cap(pax),
            pam = u3qc_mas(pax);
    if ( pam < 4 || 3 != pay || 3 != u3qc_cap(pam) ) {
      // parent axis includes sample :(
      sit_u->jet_o = c3n;
    }
    else {
      sit_u->jet_o = _cj_nail(loc, 2,
        &(sit_u->lab), &(sit_u->cop_u), &(sit_u->ham_u));
    }
    u3z(pam);
  }
  u3t_off(glu_o);
}

/* u3j_gate_slam(): slam a site prepared by u3j_gate_find() with sample.
 *                  sam is TRANSFERRED.
 */
u3_noun
u3j_gate_slam(u3j_site* sit_u, u3_noun sam)
{
  u3_weak pro;
  u3_noun cor;

  u3t_on(glu_o);
  pro = u3_none;
  cor = u3nt(u3k(u3h(sit_u->bat)),
             sam,
             u3k(u3t(u3t(sit_u->bat))));
  if ( (u3_none != sit_u->loc) && (c3y == sit_u->jet_o) ) {
    pro = _cj_site_kick_hot(cor, sit_u);
  }
  if ( u3_none == pro ) {
    pro = _cj_burn(sit_u->pog_p, cor);
  }
  u3t_off(glu_o);
  return pro;
}

/* u3j_gate_lose(): clean up site prepared by u3j_gate_find().
 */
void
u3j_gate_lose(u3j_site* sit_u)
{
  u3z(sit_u->bat);
  if ( u3_none != sit_u->loc ) {
    u3z(sit_u->loc);
    u3z(sit_u->lab);
  }
}

/* _cj_jit(): generate arbitrary warm jet-associated data.  RETAIN.
*/
static u3_noun 
_cj_jit(c3_l jax_l, u3_noun bat)
{
  return u3_nul;
}

/* _cj_mine_par_old(): register hooks and parent location within existing
 *                     axis in ancestor list or u3_none. RETAIN.
 */
static u3_weak
_cj_mine_par_old(u3_noun lan, u3_noun axe, u3_noun pel, u3_noun loc)
{
  u3_noun par;
  if ( u3_nul == lan ) {
    return u3_none;
  }
  else if ( c3y == u3r_sing(axe, u3h(par = u3h(lan))) ) {
    u3_noun lol = u3qdb_put(u3t(par), pel, loc),
            rap = u3nc(u3k(axe), lol);
    return u3nc(rap, u3k(u3t(lan)));
  }
  else {
    u3_weak nex = _cj_mine_par_old(u3t(lan), axe, pel, loc);
    if ( u3_none == nex ) {
      return u3_none;
    }
    else {
      return u3nc(u3k(par), nex);
    }
  }
}

/* _cj_mine_par_new(): insert ancestor within lan at sorted index. RETAIN.
 */
static u3_noun
_cj_mine_par_new(u3_noun lan, u3_noun axe, u3_noun pel, u3_noun loc)
{
  u3_noun par;
  if ( (u3_nul == lan) || (c3y == u3qa_lth(axe, u3h(u3h(lan)))) ) {
    par = u3nc(u3k(axe), u3qdb_put(u3_nul, pel, loc));
    return u3nc(par, u3k(lan));
  }
  else {
    return u3nc(u3k(u3h(lan)),
                _cj_mine_par_new(u3t(lan), axe, pel, loc));
  }
}

/* _cj_mine_par(): register a location as an ancestor in a list of ancestors.
 *                 RETAIN.
 */
static u3_noun
_cj_mine_par(u3_noun lan, u3_noun axe, u3_noun pel, u3_noun loc)
{
  u3_weak old = _cj_mine_par_old(lan, axe, pel, loc);
  if ( u3_none != old ) {
    return old;
  }
  else {
    return _cj_mine_par_new(lan, axe, pel, loc);
  }
}

/* _cj_mine(): declare a core and produce location. RETAIN.
*/
static u3_weak
_cj_mine(u3_noun cey, u3_noun cor)
{
  c3_l par_l, jax_l;
  u3_noun bat = u3h(cor),
          hap, reg, loc, bal, act, nam, axe, huc, ger;

  u3x_trel(cey, &nam, &axe, &huc);
  if ( 0 == axe ) {
    u3_noun pay = u3t(cor);
    reg   = _cj_find_cold(bat);
    loc   = u3nt(u3nt(c3y, c3y, u3k(pay)), u3k(nam), u3k(huc));
    if ( u3_none == reg ) {
      reg = u3nc(u3_nul, u3_nul);
    }
    ger   = u3nc(u3qdb_put(u3h(reg), pay, loc), u3k(u3t(reg)));
    u3z(reg);
    reg   = ger;
    bal   = u3nc(u3k(nam), u3_nul);
    par_l = 0;
  }
  else {
    u3_weak par, pel, pac;
    u3_noun pat;

    par = u3r_at(axe, cor);
    if ( u3_none == par || c3n == u3du(par) ) {
      fprintf(stderr, "fund: %s is bogus\r\n", u3r_string(nam));
      return u3_none;
    }
    pel = _cj_spot(par);
    if ( u3_none == pel ) {
      fprintf(stderr, "fund: in %s, parent %x not found at %d\r\n", 
                      u3r_string(nam),
                      u3r_mug(u3h(par)),
                      axe);
      return u3_none;
    }
    pac = _cj_find_warm(pel);
    c3_assert(u3_none != pac);
    par_l = u3h(pac);
    bal   = u3nc(u3k(nam), u3k(u3h(u3t(u3t(pac)))));
    u3z(pac);
    pat = ( ( 3 == axe ) && (c3y == u3h(u3h(pel))) )
        ? u3nt(c3y, c3n, u3k(pel))
        : u3nt(c3n, u3k(axe), u3k(pel));
    loc = u3nt(pat, u3k(nam), u3k(huc));
    reg = _cj_find_cold(bat);
    if ( u3_none == reg ) {
      reg = u3nc(u3_nul, u3_nul);
    }
    ger = u3nc(u3k(u3h(reg)),
               _cj_mine_par(u3t(reg), axe, pel, loc));
    u3z(pel); u3z(reg);
    reg = ger;
  }
  jax_l = _cj_hot_mean(par_l, nam);
#if 0
  u3m_p("new jet", bal);
  fprintf(stderr, "  bat %x, jax %d\r\n", u3r_mug(bat), jax_l);
#endif
  hap   = _cj_warm_hump(jax_l, huc);
  act   = u3nq(jax_l, hap, bal, _cj_jit(jax_l, bat));
  u3h_put(u3R->jed.cod_p, bat, reg);
  u3h_put(u3R->jed.war_p, loc, act);

  return loc;
}

/* _cj_moan(): register core known to be unregistered, returning
 *             location. clu and cor are TRANSFERRED.
 */
static u3_weak
_cj_moan(u3_noun clu, u3_noun cor)
{
  u3_weak cey = _cj_je_fsck(clu);
  u3_weak loc = u3_none;
  if ( u3_none != cey ) {
    loc = _cj_mine(cey, cor);
    u3z(cey);
  }
  u3z(cor);
  return loc;
}

/* _cj_mile(): register core for jets, returning location.
*/
static u3_weak
_cj_mile(u3_noun clu, u3_noun cor)
{
  u3_weak loc = u3_none;
  if ( c3n == u3du(cor) ) {
    u3z(clu);
    u3z(cor);
  }
  else {
    loc = _cj_spot(cor);
    if ( u3_none == loc ) {
      loc = _cj_moan(clu, cor);
    }
    else {
      u3z(clu);
      u3z(cor);
    }
  }
  return loc;
}

/* u3j_mine(): register core for jets.
*/
void
u3j_mine(u3_noun clu, u3_noun cor)
{
  u3t_on(glu_o);
  if ( (c3n == u3du(cor)) || (c3y == _cj_scan(cor)) ) {
    u3z(clu);
    u3z(cor);
  }
  else {
    u3_weak loc = _cj_moan(clu, cor);
    if ( u3_none != loc ) {
      u3z(loc);
    }
  }
  u3t_off(glu_o);
}

/* u3j_rite_mine(): mine cor with clue, using u3j_rite for caching
*/
void
u3j_rite_mine(u3j_rite* rit_u, u3_noun clu, u3_noun cor)
{
  c3_t non_t;
  u3t_on(glu_o);

  non_t = (u3_none == rit_u->clu);

  if ( non_t ||
       c3n == u3r_sing(rit_u->clu, clu) ||
       c3n == _cj_fine(cor, rit_u->fin_p) ) {
    u3_weak loc = _cj_mile(u3k(clu), u3k(cor));
    if ( u3_none != loc ) {
      u3p(u3j_fink) fon_p = rit_u->fin_p;
      u3_noun   old   = rit_u->clu;
      c3_o      own_o = rit_u->own_o;
      rit_u->own_o    = c3y;
      rit_u->clu      = u3k(clu);
      rit_u->fin_p    = _cj_cast(cor, loc);
      u3z(loc);

      if ( !non_t && (c3y == own_o) ) {
         u3z(old);
        _cj_fink_free(fon_p);
      }
    }
  }
  u3z(clu);
  u3z(cor);
  u3t_off(glu_o);
}

/* _cj_warm_reap(): reap key and value from warm table.
*/
static void
_cj_warm_reap(u3_noun kev)
{
  u3_noun loc = u3a_take(u3h(kev));
  u3_noun act = u3a_take(u3t(kev));
  u3h_put(u3R->jed.war_p, loc, act);
  u3z(loc);
}

/* _cj_uni_jun(): merge junior map into senior map.
 *                sem is TRANSFERRED.
 *                jum is RETAINED.
 */
static u3_noun
_cj_uni_jun(u3_noun sem, u3_noun jum)
{
  if ( u3_nul == jum ) {
    return sem;
  }
  else {
    u3_noun n, l, r;
    u3x_trel(jum, &n, &l, &r);
    sem = _cj_uni_jun(sem, l);
    sem = _cj_uni_jun(sem, r);
    return u3kdb_put(sem, u3a_take(u3h(n)), u3a_take(u3t(n)));
  }
}

/* _cj_remarry(): merge parent lists.
 *                sel is TRANSFERRED.
 *                jul is RETAINED.
 */
static u3_noun
_cj_remarry(u3_noun sel, u3_noun jul)
{
  if ( u3_nul == sel ) {
    return u3a_take(jul);
  }
  else if ( u3_nul == jul ) {
    return sel;
  }
  else {
    u3_noun sap = u3h(sel),
            jup = u3h(jul),
            sax = u3h(sap),
            jux = u3h(jup);
    if ( c3y == u3r_sing(sax, jux) ) {
      u3_noun lol = _cj_uni_jun(u3k(u3t(sap)), u3t(jup)),
              par = u3nc(u3k(u3h(sap)), lol),
              nex = _cj_remarry(u3k(u3t(sel)), u3t(jul)),
              pro = u3nc(par, nex);
      u3z(sel);
      return pro;
    }
    else if ( c3y == u3qa_lth(sax, jux) ) {
      u3_noun nex = _cj_remarry(u3k(u3t(sel)), jul),
              pro = u3nc(u3k(sap), nex);
      u3z(sel);
      return pro;
    }
    else {
      return u3nc(u3a_take(jup), _cj_remarry(sel, u3t(jul)));
    }
  }
}

/* _cj_cold_reap(): reap cold dashboard entries.
 */
static void
_cj_cold_reap(u3_noun kev)
{
  u3_noun jur = u3t(kev);
  u3_noun bat = u3a_take(u3h(kev));
  u3_weak ser = _cj_find_cold(bat);
  u3_noun reg = ( u3_none == ser )
              ? u3a_take(jur)
              : u3nc(_cj_uni_jun(u3k(u3h(ser)), u3h(jur)),
                     _cj_remarry(u3k(u3t(ser)), u3t(jur)));
  u3h_put(u3R->jed.cod_p, bat, reg);
  u3z(ser); u3z(bat);
}

/* _cj_hank_reap(): reap hook resolutions.
 */
static void
_cj_hank_reap(u3_noun kev)
{
  u3_noun   key   = u3a_take(u3h(kev));
  u3_noun   got   = u3h_git(u3R->jed.han_p, key);
  _cj_hank* nah_u = u3to(_cj_hank, u3t(kev));
  _cj_hank* han_u;

  if ( u3_none != got ) {
    if ( u3_none != nah_u->hax ) {
      u3_weak old;
      han_u = u3to(_cj_hank, got);
      old = han_u->hax;
      han_u->hax = u3a_take(nah_u->hax);
      u3j_site_copy(&(han_u->sit_u), &(nah_u->sit_u), c3y);
      if ( u3_none != old ) {
        u3z(old);
      }
    }
  }
  else if ( u3_none != nah_u->hax ) {
    han_u      = u3a_walloc(c3_wiseof(_cj_hank));
    han_u->hax = u3a_take(nah_u->hax);
    u3j_site_copy(&(han_u->sit_u), &(nah_u->sit_u), c3n);
    u3h_put(u3R->jed.han_p, key, u3a_outa(han_u));
  }

  u3z(key);
}

/* u3j_reap(): promote jet state.
*/
void
u3j_reap(u3p(u3h_root) cod_p, u3p(u3h_root) war_p, u3p(u3h_root) han_p)
{
  u3h_walk(cod_p, _cj_cold_reap);
  u3h_walk(war_p, _cj_warm_reap);
  u3h_walk(han_p, _cj_hank_reap);
}

/* _cj_ream(): ream list of battery registry pairs. RETAIN.
 */
static void
_cj_ream(u3_noun all)
{
  c3_l par_l, jax_l;
  u3_noun i, j, k, rul, loc, bal, act, lop, kev, rut, hap,
          pat, reg, pol, rem, rec, bat, pel, nam, huc;
  u3_weak pac;

  for ( i = all, lop = u3_nul; i != u3_nul; i = u3t(i) ) {
    kev = u3h(i);
    bat = u3h(kev);
    reg = u3t(kev);
    rut = u3h(reg);

    // register roots
    rul   = u3qdb_tap(rut);
    for ( j = rul; j != u3_nul; j = u3t(j) ) {
      loc   = u3t(u3h(j));
      u3x_trel(loc, &pat, &nam, &huc);
      bal   = u3nc(u3k(nam), u3_nul);
      jax_l = _cj_hot_mean(0, nam);
      hap   = _cj_warm_hump(jax_l, huc);
      act   = u3nq(jax_l, hap, bal, _cj_jit(jax_l, bat));
#if 0
      u3m_p("old jet", bal);
      fprintf(stderr, "  bat %x, jax %d\r\n", u3r_mug(bat), jax_l);
#endif
      u3h_put(u3R->jed.war_p, loc, act);
    }
    u3z(rul);

    // put ancestors in lop (list [battery=^ parent=location this=location])
    for ( j = u3t(reg); j != u3_nul; j = u3t(j) ) {
      pol = lop;
      lop = u3qdb_tap(u3t(u3h(j)));
      for ( k = lop; u3_nul != k; k = u3t(k) ) {
        pol = u3nc(u3nc(u3k(bat), u3k(u3h(k))), pol);
      }
      u3z(lop);
      lop = pol;
    }
  }

  // ordering is random so we need to push onto rem when parent
  // isn't yet present in the warm state
  while ( u3_nul != lop ) {
    rem = u3_nul;
    for ( i = lop; u3_nul != i; i = u3t(i) ) {
      rec = u3h(i);
      u3x_trel(rec, &bat, &pel, &loc);
      pac = _cj_find_warm(pel);
      if ( u3_none == pac ) {
        rem = u3nc(u3k(rec), rem);
      }
      else {
        u3x_trel(loc, &pat, &nam, &huc);
        par_l = u3h(pac);
        jax_l = _cj_hot_mean(par_l, nam);
        bal   = u3nc(u3k(nam), u3k(u3h(u3t(u3t(pac)))));
        hap   = _cj_warm_hump(jax_l, huc),
        u3z(pac);
        act   = u3nq(jax_l, hap, bal, _cj_jit(jax_l, bat));
#if 0
        u3m_p("old jet", bal);
        fprintf(stderr, "  bat %x, jax %d\r\n", u3r_mug(bat), jax_l);
#endif
        u3h_put(u3R->jed.war_p, loc, act);
      }
    }
    u3z(lop);
    lop = rem;
  }
}

/* _cj_warm_tap(): tap war_p to rel
*/
static void
_cj_warm_tap(u3_noun kev, void* wit)
{
  u3_noun* rel = wit;
  *rel = u3nc(u3k(kev), *rel);
}

/* _cj_ream_hank(): clear hot state out of hook sites.
*/
static void
_cj_ream_hank(u3_noun kev)
{
  u3j_site_ream(&(u3to(_cj_hank, u3t(kev))->sit_u));
}

/* u3j_ream(): rebuild warm state
*/
void
u3j_ream(void)
{
  u3_noun rel = u3_nul;
  u3h_free(u3R->jed.war_p);
  u3R->jed.war_p = u3h_new();
  c3_assert(u3R == &(u3H->rod_u));
  u3h_walk_with(u3R->jed.cod_p, _cj_warm_tap, &rel);
  _cj_ream(rel);
  u3z(rel);

  u3h_walk(u3R->jed.han_p, _cj_ream_hank);
}

/* _cj_fink_mark(): mark a u3j_fink for gc.
*/
static c3_w
_cj_fink_mark(u3j_fink* fin_u)
{
  c3_w i_w, tot_w = u3a_mark_noun(fin_u->sat);
  for ( i_w = 0; i_w < fin_u->len_w; ++i_w ) {
    u3j_fist* fis_u = &(fin_u->fis_u[i_w]);
    tot_w += u3a_mark_noun(fis_u->bat);
    tot_w += u3a_mark_noun(fis_u->pax);
  }
  tot_w += u3a_mark_ptr(fin_u);
  return tot_w;
}

/* u3j_site_lose(): lose references of u3j_site (but do not free).
 */
void
u3j_site_lose(u3j_site* sit_u)
{
  u3z(sit_u->axe);
  if ( u3_none != sit_u->bat ) {
    u3z(sit_u->bat);
  }
  if ( u3_none != sit_u->loc ) {
    u3z(sit_u->loc);
    u3z(sit_u->lab);
    if ( c3y == sit_u->fon_o ) {
      _cj_fink_free(sit_u->fin_p);
    }
  }
}

/* u3j_rite_lose(): lose references of u3j_rite (but do not free).
 */
void
u3j_rite_lose(u3j_rite* rit_u)
{
  if ( (c3y == rit_u->own_o) && u3_none != rit_u->clu ) {
    u3z(rit_u->clu);
    _cj_fink_free(rit_u->fin_p);
  }
}

/* u3j_rite_mark(): mark u3j_rite for gc.
*/
c3_w
u3j_rite_mark(u3j_rite* rit_u)
{
  c3_w tot_w = 0;
  if ( (c3y == rit_u->own_o) && u3_none != rit_u->clu ) {
    tot_w += u3a_mark_noun(rit_u->clu);
    tot_w += _cj_fink_mark(u3to(u3j_fink, rit_u->fin_p));
  }
  return tot_w;
}

/* u3j_site_mark(): mark u3j_site for gc.
*/
c3_w
u3j_site_mark(u3j_site* sit_u)
{
  c3_w tot_w = u3a_mark_noun(sit_u->axe);
  if ( u3_none != sit_u->bat ) {
    tot_w += u3a_mark_noun(sit_u->bat);
  }
  if ( u3_none != sit_u->loc ) {
    tot_w += u3a_mark_noun(sit_u->loc);
    tot_w += u3a_mark_noun(sit_u->lab);
    if ( c3y == sit_u->fon_o ) {
      tot_w += _cj_fink_mark(u3to(u3j_fink, sit_u->fin_p));
    }
  }
  return tot_w;
}

/* _cj_mark_hank(): mark hank cache for gc.
*/
static void
_cj_mark_hank(u3_noun kev, void* dat)
{
  c3_w* tot_w = (c3_w*) dat;
  _cj_hank* han_u = u3to(_cj_hank, u3t(kev));
  *tot_w += u3a_mark_ptr(han_u);
  if ( u3_none != han_u->hax ) {
    *tot_w += u3a_mark_noun(han_u->hax);
    *tot_w += u3j_site_mark(&(han_u->sit_u));
  }
}

/* u3j_mark(): mark jet state for gc.
*/
c3_w
u3j_mark(void)
{
  c3_w tot_w = 0;
  tot_w += u3h_mark(u3R->jed.war_p);
  tot_w += u3h_mark(u3R->jed.cod_p);
  tot_w += u3h_mark(u3R->jed.han_p);
  u3h_walk_with(u3R->jed.han_p, _cj_mark_hank, &tot_w);
  return tot_w;
}

/* _cj_free_hank(): free hank cache.
*/
static void
_cj_free_hank(u3_noun kev)
{
  _cj_hank* han_u = u3to(_cj_hank, u3t(kev));
  if ( u3_none != han_u->hax ) {
    u3z(han_u->hax);
    u3j_site_lose(&(han_u->sit_u));
  }
  u3a_wfree(han_u);
}

/* u3j_free(): free jet state.
*/
void
u3j_free(void)
{
  u3h_walk(u3R->jed.han_p, _cj_free_hank);
  u3h_free(u3R->jed.war_p);
  u3h_free(u3R->jed.cod_p);
  u3h_free(u3R->jed.han_p);
}

