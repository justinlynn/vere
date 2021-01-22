import React, { useRef, useCallback, useEffect, useMemo } from "react";
import { Col } from "@tlon/indigo-react";
import bigInt from 'big-integer';
import {
  Association,
  Graph,
  Contacts,
  Unreads,
  LocalUpdateRemoteContentPolicy,
  Group,
  Rolodex,
  S3State,
} from "~/types";
import GlobalApi from "~/logic/api/global";
import VirtualScroller from "~/views/components/VirtualScroller";
import { LinkItem } from "./components/LinkItem";
import LinkSubmit from "./components/LinkSubmit";

interface LinkWindowProps {
  association: Association;
  contacts: Rolodex;
  resource: string;
  graph: Graph;
  unreads: Unreads;
  hideNicknames: boolean;
  hideAvatars: boolean;
  baseUrl: string;
  group: Group;
  path: string;
  api: GlobalApi;
  s3: S3State;
}
export function LinkWindow(props: LinkWindowProps) {
  const { graph, api, association } = props;
  const loadedNewest = useRef(true);
  const loadedOldest = useRef(false);
  const virtualList = useRef<VirtualScroller>();
  const fetchLinks = useCallback(
    async (newer: boolean) => {
      /* stubbed, should we generalize the display of graphs in virtualscroller? */
    }, []
  );

  useEffect(() => {
    const list = virtualList?.current;
    if(!list) return;
    list.calculateVisibleItems();
  }, [graph.size]);

  const first = graph.peekLargest()?.[0];

  const [,,ship, name] = association['app-path'].split('/');

  const style = useMemo(() =>
    ({
      height: "100%",
      width: "100%",
      display: 'flex',
      flexDirection: 'column',
      alignItems: 'center'
    }), []);

  return (
    <VirtualScroller
      ref={(l) => (virtualList.current = l ?? undefined)}
      origin="top"
      style={style}
      onStartReached={() => {}}
      onScroll={() => {}}
      data={graph}
      size={graph.size}
      renderer={({ index, measure, scrollWindow }) => {
        const node = graph.get(index);
        const post = node?.post;
        if (!node || !post) return null;
        const linkProps = {
          ...props,
          node,
          measure,
          key: index.toString()
        };
        if(index.eq(first ?? bigInt.zero)) {
          return (
            <>
            <Col key={index.toString()} mx="auto" mt="4" maxWidth="768px" width="100%" flexShrink='0' px={3}>
              <LinkSubmit s3={props.s3} name={name} ship={ship.slice(1)} api={api} />
            </Col>
              <LinkItem {...linkProps} />
            </>
          )
        }
        return <LinkItem {...linkProps} />;
      }}
      loadRows={fetchLinks}
    />
  );
}
