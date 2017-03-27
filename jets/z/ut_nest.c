/* j/6/ut_nest.c
**
*/
#include "all.h"

/* logic
*/
  /* forward
  */
    static u3_noun
    _nest_sint(u3_noun, u3_noun, u3_noun, u3_noun, u3_noun, u3_noun, u3_noun);
    static u3_noun
    _nest_dext(u3_noun, u3_noun, u3_noun, u3_noun, u3_noun, u3_noun, u3_noun);

  static u3_noun
  _nest_deep(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref,
             u3_noun dab,
             u3_noun hem,
             u3_noun gil)
  {
    if ( u3_nul == dab ) {
      return u3r_sing(u3_nul, hem);
    } else if ( u3_nul == hem ) {
      return c3n;
    } else {
      u3_noun n_dab, l_dab, r_dab;
      u3_noun n_hem, l_hem, r_hem;
      u3_noun pn_hem, pqn_hem, qqn_hem, pn_dab, pqn_dab, qqn_dab;

      u3x_trel(dab, &n_dab, &l_dab, &r_dab);
      u3x_trel(hem, &n_hem, &l_hem, &r_hem);

      if ( (c3n == _nest_deep(van, sut, tel, ref, l_dab, l_hem, gil)) ||
           (c3n == _nest_deep(van, sut, tel, ref, r_dab, r_hem, gil)) ) 
      {
        return c3n;
      }
      u3x_trel(n_dab, &pn_dab, &pqn_dab, &qqn_dab);
      u3x_trel(n_hem, &pn_hem, &pqn_hem, &qqn_hem);

      if ( c3n == u3r_sing(pn_dab, pn_hem) ) {
        return c3n;
      } else {
        if ( (c3n == u3du(qqn_dab)) || (c3n == u3du(qqn_hem)) ) {
          return u3m_bail(c3__fail);
        }
        else switch ( u3h(qqn_dab) ) {
          default: return u3m_bail(c3__exit);
          case c3__ash: {
            if ( c3__ash != u3h(qqn_hem) ) {
              return c3n;
            } else {
              u3_noun qqqn_dab = u3t(qqn_dab);
              u3_noun qqqn_hem = u3t(qqn_hem);
              u3_noun vis = u3qzu_play(van, sut, qqqn_dab);
              u3_noun lon = u3qzu_play(van, ref, qqqn_hem);
 
              u3_noun ret = _nest_dext(van, vis, tel, lon, u3_nul, u3_nul, gil);

              u3z(vis);
              u3z(lon);
              return ret;
            }
          }
          case c3__elm: {
            return u3r_sing(qqn_dab, qqn_hem);
          }
        }
      }
    }
  }

  static u3_noun
  _nest_dope(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref,
             u3_noun dom,
             u3_noun vim,
             u3_noun gil)
  {
    if ( u3_nul == dom ) {
      return u3r_sing(u3_nul, vim);
    } else if ( u3_nul == vim ) {
      return c3n;
    } else {
      u3_noun n_dom, l_dom, r_dom;
      u3_noun n_vim, l_vim, r_vim;
      u3_noun pn_vim, pqn_vim, qqn_vim, pn_dom, pqn_dom, qqn_dom;

      u3x_trel(dom, &n_dom, &l_dom, &r_dom);
      u3x_trel(vim, &n_vim, &l_vim, &r_vim);

      if ( (c3n == _nest_dope(van, sut, tel, ref, l_dom, l_vim, gil)) ||
           (c3n == _nest_dope(van, sut, tel, ref, r_dom, r_vim, gil)) ) 
      {
        return c3n;
      }
      u3x_trel(n_dom, &pn_dom, &pqn_dom, &qqn_dom);
      u3x_trel(n_vim, &pn_vim, &pqn_vim, &qqn_vim);

      if ( c3n == u3r_sing(pn_dom, pn_vim) ) {
        return c3n;
      } else {
        return _nest_deep(van, sut, tel, ref, qqn_dom, qqn_vim, gil);
      }
    }
  }

  static u3_noun
  _nest_cong(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref,
             u3_noun gil)
  {
    u3_noun p_sut, q_sut, p_ref, q_ref;
    u3_noun pq_sut, qq_sut, rq_sut;
    u3_noun pq_ref, qq_ref, rq_ref;
    u3_noun prq_sut, qrq_sut, prq_ref, qrq_ref;
    u3_noun ret;

    u3x_trel(sut, 0, &p_sut, &q_sut);
    u3x_trel(ref, 0, &p_ref, &q_ref);

    u3x_trel(q_sut, &pq_sut, &qq_sut, &rq_sut);
    u3x_trel(q_ref, &pq_ref, &qq_ref, &rq_ref);

    u3x_cell(rq_sut, &prq_sut, &qrq_sut);
    u3x_cell(rq_ref, &prq_ref, &qrq_ref);

    if ( c3y == u3r_sing(q_sut, q_ref) ) {
      return _nest_dext(van, p_sut, tel, p_ref, u3_nul, u3_nul, gil);
    }
    else if ( (c3n == _nest_dext
                        (van, qq_sut, tel, p_sut, u3_nul, u3_nul, gil)) ||
              (c3n == _nest_dext
                        (van, p_sut, tel, qq_sut, u3_nul, u3_nul, gil)) ||
              (c3n == _nest_dext
                        (van, qq_ref, tel, p_ref, u3_nul, u3_nul, gil)) )
    {
      return c3n;
    }
    else {
      if ( (pq_sut != pq_ref) && 
           (c3__lead != pq_sut) &&
           (c3__gold != pq_ref) ) 
      {
        return c3n;
      }
      else {
        u3_noun hud = u3nc(u3k(sut), u3k(ref));

        if ( (c3y == u3qdi_has(gil, hud)) ) {
          u3z(hud);

          return c3y;
        }
        else {
          u3_noun zoc = u3qdi_put(gil, hud);
          u3_noun tus = u3nt(c3__core,
                             u3k(qq_sut),
                             u3nc(c3__gold,
                                  u3k(u3t(q_sut))));

          u3_noun fer = u3nt(c3__core,
                             u3k(qq_ref),
                             u3nc(c3__gold,
                                  u3k(u3t(q_ref))));

          ret = _nest_dope(van, tus, tel, fer, qrq_sut, qrq_ref, zoc);
          u3z(fer);
          u3z(tus);
          u3z(zoc);
          u3z(hud);

          if ( c3n == ret ) {
            return c3n;
          }
          else {
            switch ( pq_sut ) {
              default: return u3m_bail(c3__fail);

              case c3__gold: {
                return
                  c3a(_nest_dext(van, qq_sut, tel, qq_ref, u3_nul, u3_nul, gil),
                      _nest_dext(van, qq_ref, tel, qq_sut, u3_nul, u3_nul, gil));
              }
              case c3__iron: {
                u3_noun s_sam = u3qzu_peek(van, qq_sut, c3__rite, 2);
                u3_noun r_sam = u3qzu_peek(van, qq_ref, c3__rite, 2);
                u3_noun ret = _nest_dext
                                (van, r_sam, tel, s_sam, u3_nul, u3_nul, gil);

                u3z(r_sam);
                u3z(s_sam);
                return ret;
              }
              case c3__lead: {
                return c3y;
              }
              case c3__zinc: {
                u3_noun s_pal = u3qzu_peek(van, qq_sut, c3__read, 2);
                u3_noun r_pal = u3qzu_peek(van, qq_ref, c3__read, 2);
                u3_noun ret = _nest_dext
                                (van, s_pal, tel, r_pal, u3_nul, u3_nul, gil);

                u3z(r_pal);
                u3z(s_pal);

                return ret;
              }
            }
          }
        }
      }
    }
  }

  static u3_noun
  _nest_dext_in(u3_noun van,
                u3_noun sut,
                u3_noun tel,
                u3_noun ref,
                u3_noun seg, 
                u3_noun reg,
                u3_noun gil)
  {
    u3_noun p_sut, q_sut, p_ref, q_ref;

    if ( (c3n == u3du(sut)) ) switch ( sut ) {
      default: return u3m_bail(c3__fail);

      case c3__noun: {
        return c3y;
      }
      case c3__void: {
        return _nest_sint(van, sut, tel, ref, seg, reg, gil);
      }
    }
    else switch ( u3h(sut) ) {
      default: return u3m_bail(c3__fail);

      case c3__atom: {
        if ( (c3n == u3r_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3m_bail(c3__fail);
        } 
        else {
          if ( c3y == u3r_pq(ref, c3__atom, &p_ref, &q_ref) ) {
            if ( (c3n == u3qz_fitz(p_sut, p_ref)) ||
                 ( (c3y == u3du(q_sut)) && 
                   ( (c3n == u3du(q_ref)) ||
                     (c3n == u3r_sing(q_sut, q_ref)))) ) 
            {
              return c3n;
            }
            return c3y;
          }
          return _nest_sint(van, sut, tel, ref, seg, reg, gil);
        }
      }
      case c3__cell: {
        if ( (c3n == u3r_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3m_bail(c3__fail);
        } else {
          if ( c3y == u3r_pq(ref, c3__cell, &p_ref, &q_ref) ) {
            return c3a(_nest_dext(van, p_sut, tel, p_ref, u3_nul, u3_nul, gil),
                       _nest_dext(van, q_sut, tel, q_ref, u3_nul, u3_nul, gil));
          }
          else return _nest_sint(van, sut, tel, ref, seg, reg, gil);
        }
      }
      case c3__core: {
        if ( c3n == u3r_trel(sut, 0, &p_sut, &q_sut) ) {
          return u3m_bail(c3__fail);
        } else {
          if ( (c3y == u3r_pq(ref, c3__core, &p_ref, &q_ref)) ) {
            return _nest_cong(van, sut, tel, ref, gil);
          }
          else return _nest_sint(van, sut, tel, ref, seg, reg, gil);
        }
      }
      case c3__help:
      case c3__face: {
        if ( (c3n == u3r_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3m_bail(c3__fail);
        } else {
          return _nest_dext(van, q_sut, tel, ref, seg, reg, gil);
        }
      }
      case c3__fork: p_sut = u3t(sut);
      {
        if ( c3n == u3du(ref) ) switch ( ref ) {
          default: return _nest_sint(van, sut, tel, ref, seg, reg, gil);

          case c3__noun:
            break;
        }
        else switch ( u3h(ref) ) {
          default: return _nest_sint(van, sut, tel, ref, seg, reg, gil);

          case c3__atom:
          case c3__cell:
          case c3__core:
            break;
        }

        {
          u3_noun dey = u3qdi_tap(p_sut, u3_nul);
          u3_noun yed = dey;

          while ( u3_nul != yed ) {
            if ( c3y == _nest_dext(van, u3h(yed), c3n, ref, seg, reg, gil) ) {
              u3z(dey);
              return c3y;
            } else {
              yed = u3t(yed);
            }
          }
          u3z(dey);
          return c3n;
        }
      }
      case c3__hold:
      {
        if ( c3y == u3qdi_has(seg, sut) ) {
          return c3n;
        }
        else {
          u3_noun hud = u3nc(u3k(sut), u3k(ref));

          if ( (c3y == u3qdi_has(gil, hud)) ) {
            u3z(hud);

            return c3y;
          } 
          else {
            u3_noun gus = u3qdi_put(seg, sut);
            u3_noun zoc = u3qdi_put(gil, hud);
            u3_noun fop = u3qzu_repo(van, sut);
            u3_noun hiv = _nest_dext(van, fop, tel, ref, gus, reg, zoc);

            u3z(hud);
            u3z(fop);
            u3z(zoc);
            u3z(gus);

            return hiv;
          }
        }
      }
    }
  }

  static u3_noun
  _nest_dext_to(u3_noun van,
                u3_noun sut,
                u3_noun tel,
                u3_noun ref,
                u3_noun seg,
                u3_noun reg,
                u3_noun gil)
  {
    u3_noun tyn = _nest_dext_in(van, sut, tel, ref, seg, reg, gil);

    if ( (c3y == tyn) || (c3n == tel) ) {
      return tyn;
    } else {
#if 0
      u3_noun dun = u3qzu_dunq(van, "need", sut);
      u3_noun niz = u3qzu_dunq(van, "have", ref);

      u3t_push(u3nc(c3__mean, dun));
      u3t_push(u3nc(c3__mean, niz));
#endif
      return u3m_error("nest-fail");
    }
  }

  static u3_noun
  _nest_dext(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref,
             u3_noun seg,
             u3_noun reg,
             u3_noun gil)
  {

    if ( (c3y == u3r_sing(sut, ref)) ) {
      return c3y;
    }

    {
      c3_m    fun_m = 146 + c3__nest + ((!!u3r_at(u3qzu_van_vet, van)) << 8);
      u3_noun pro   = u3z_find_2(fun_m, sut, ref);

      if ( u3_none != pro ) {
        return pro;
      }
      else {
        pro = _nest_dext_to(van, sut, tel, ref, seg, reg, gil);

        if ( ((c3y == pro) && (u3_nul == reg)) || 
             ((c3n == pro) && (u3_nul == seg)) ) 
        {
          return u3z_save_2(fun_m, sut, ref, pro);
        }
        else return pro;
      }
    }
  }

  static u3_noun
  _nest_sint(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref,
             u3_noun seg,
             u3_noun reg,
             u3_noun gil)
  {
    u3_noun p_ref, q_ref;

    if ( (c3n == u3du(ref)) ) {
      switch ( ref ) {
        default: return u3m_bail(c3__fail);

        case c3__noun: return c3n;
        case c3__void: return c3y;
      }
    }
    else {
      switch ( u3h(ref) ) {
        default: {
          return u3m_bail(c3__fail);
        }
        case c3__atom: return c3n;
        case c3__cell: return c3n;
        case c3__core: {
          u3_noun gam = u3qzu_repo(van, ref);
          u3_noun hiv = _nest_dext(van, sut, tel, gam, seg, reg, gil);

          u3z(gam);
          return hiv;
        }
        case c3__help:
        case c3__face: {
          if ( c3n == u3r_trel(ref, 0, &p_ref, &q_ref) ) {
            return u3m_bail(c3__fail);
          } else {
            return _nest_dext(van, sut, tel, q_ref, seg, reg, gil);
          }
        }
        case c3__fork: p_ref = u3t(ref);
        {
          u3_noun dey = u3qdi_tap(p_ref, u3_nul);
          u3_noun yed = dey;

          while ( u3_nul != yed ) {
            if ( c3n == _nest_dext(van, sut, c3n, u3h(yed), seg, reg, gil) ) {
              u3z(dey);
              return c3n;
            } else {
              yed = u3t(yed);
            }
          }
          u3z(dey);
          return c3y;
        }
        case c3__hold: {
          if ( c3y == u3qdi_has(reg, ref) ) {
            return c3y;
          }
          {
            u3_noun hud = u3nc(u3k(sut), u3k(ref));

            if ( (c3y == u3qdi_has(gil, hud)) ) {
              u3z(hud);

              return c3y;
            } else {
              u3_noun gur = u3qdi_put(reg, ref);
              u3_noun zoc = u3qdi_put(gil, hud);
              u3_noun gam = u3qzu_repo(van, ref);

              {
                u3_noun hiv = _nest_dext(van, sut, tel, gam, seg, gur, zoc);

                u3z(hud);
                u3z(gam);
                u3z(zoc);
                u3z(gur);

                return hiv;
              }
            }
          }
        }
      }
    }
  }

  u3_noun
  _cqzu_nest(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref)
  {
    return _nest_dext(van, sut, tel, ref, u3_nul, u3_nul, u3_nul);
  }

/* boilerplate
*/
  u3_noun
  u3wzu_nest(u3_noun cor)
  {
    u3_noun sut, tel, ref, van;

    if ( (c3n == u3r_mean(cor, u3x_sam_2, &tel,
                               u3x_sam_3, &ref,
                               u3x_con, &van,
                               0)) ||
         (c3n == u3ud(tel)) || (tel > 1) ||
         (u3_none == (sut = u3r_at(u3x_sam, van))) )
    {
      return u3m_bail(c3__fail);
    } else {
      return _cqzu_nest(van, sut, tel, ref);
    }
  }

  u3_noun
  u3qzu_nest(u3_noun van,
             u3_noun sut,
             u3_noun tel,
             u3_noun ref)
  {
    return _cqzu_nest(van, sut, tel, ref);
  }

